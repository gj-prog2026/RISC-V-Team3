# Data Cache

The data cache sits in the MEM stage between the CPU and main (data) memory. A
load/store unit (LSU) handles all byte/halfword work, so the cache itself only
stores and returns aligned 32-bit words. Whenever the cache cannot answer in the
same cycle it raises `stall` to the hazard unit.

## Overview: design progression

1. **Direct-mapped, b = 1** (block size 1 word, so no word-select mux). This is
   the baseline and the version being implemented now.
2. **2-way set associative** for a lower miss rate: two addresses that share a
   set no longer evict each other every time.
3. **Larger blocks (4 words)** for spatial locality: one memory access fetches
   several consecutive words, which reduces cold (compulsory) misses, but with
   the same capacity there are fewer sets, so conflict misses can increase.

## Direct-mapped cache (b = 1)

| Parameter    | Value                                                  |
|--------------|--------------------------------------------------------|
| Sets         | 64, one 32-bit word each (256 B of data)               |
| Address      | Tag `[31:8]` (24 b), Set `[7:2]` (6 b), Byte offset `[1:0]` (used only by the LSU) |
| Arrays       | V-flag (1 b), Tag (24 b), Data (32 b), indexed by a 6-to-64 row decoder |
| Write policy | Write-through, no-write-allocate, no dirty bit         |
| Main memory  | 128 KB, `ram[0:32767]` of 32-bit words, word index `mem_addr[16:2]` |

### Hit, miss, stall and fill

```
hit   = V[set] && (Tag[set] == addr[31:8])
miss  = rd_en && !hit
stall = (state != IDLE) || (rd_en && !hit) || wr_en
fill  = read miss && mem_ready
```

On a **fill** the indexed row is written in one cycle: `V = 1`,
`Tag = addr[31:8]`, `Data[set] = mem_rdata`. Writing only the data is not
enough, or the same address would miss forever.

Array write enable: `(wr_en && hit) || fill`, where `wr_en = MemWrite`.

### Write port

Two sources can write the arrays, selected by `fill`:

```
wdata   = fill ? mem_rdata : wr_data       // 32 b
byte_en = fill ? 4'b1111   : lsu_byte_en   // 4 b
```

On a store hit only the bytes with `byte_en = 1` change. A fill replaces the
whole word. See `write_port_mux.pdf`.

### FSM

| From      | Condition       | To        | Action                         |
|-----------|-----------------|-----------|--------------------------------|
| IDLE      | `rd_en && !hit` | READ_MISS | `mem_req = 1`, `mem_wr = 0`    |
| READ_MISS | `mem_ready`     | IDLE      | `fill = 1`                     |
| IDLE      | `wr_en`         | WRITE     | `mem_req = 1`, `mem_wr = 1`, `mem_byte_en`, `mem_wdata` |
| WRITE     | `mem_ready`     | IDLE      | store committed to memory      |

`mem_addr` comes from `address[31:0]` (= `alu_result`). The FSM holds
`mem_req`, `mem_addr`, `mem_wdata` and `mem_byte_en` stable until `mem_ready`.

## LSU

**Before the cache (stores):** the LSU drives the memory address, a 4-bit
`byte_en` mask and the store data replicated into every lane:

| Instr | `byte_en` (offset 0 / 1 / 2 / 3)     | `wr_data`                |
|-------|--------------------------------------|--------------------------|
| SB    | `0001` / `0010` / `0100` / `1000`    | `{4{rs2[7:0]}}`          |
| SH    | `0011` / – / `1100` / –              | `{2{rs2[15:0]}}`         |
| SW    | `1111`                               | `rs2`                    |

The mask is shifted **left** by the offset for stores; the cache writes
`wr_data` only into the bytes whose `byte_en = 1`.

**After the cache (loads):** the LSU takes `rd_data`, shifts it **right** by
`addr[1:0] * 8` (offset 0, 1, 2, 3 gives shift 0, 8, 16, 24), then sign-extends
(LB, LH) or zero-extends (LBU, LHU) and returns `load_data` to the CPU.

LSU ports: inputs `rs2_data`, `alu_result`, `funct3`, `rd_data`; outputs
`addr`, `wr_data`, `byte_en`, `load_data`.

## 2-way set associative: victim and LRU

Victim selection (combinational) on a read miss:

1. Use an empty (invalid) way if there is one.
2. If both ways are full, use the LRU way: `victim = lru_q[set]`.

LRU (one bit per set, pointing at the way to replace next):

- Update only on a hit or a fill; otherwise keep the old value.
- On a hit: `lru_q[set] = !hit_way`.
- On a fill: `lru_q[set] = !victim`.

A mux finds which way has `hit = 1`; inverting it marks the other way as least
recently used, so it is replaced next.

## Files

| Path                                   | What it is |
|----------------------------------------|------------|
| `rtl/data_cache.sv`                    | Cache module. **Currently the earlier 2-way, 4-word-block, write-back prototype**; to be replaced by the direct-mapped write-through version above. |
| `rtl/main_memory.sv`                   | Main memory. Folder copy is the 128-bit (4-word block) version; the 32-bit `byte_en` version for b = 1 is the one to use with the direct-mapped cache. |
| `rtl/cache_top.sv`                     | Test wrapper: cache + main memory. |
| `tb/cache_tb.cpp`                      | Verilator testbench (directed tests + 20,000 random accesses vs a shadow memory), written for the 2-way prototype. |
| `run_cache_tb.sh`                      | Builds with Verilator and runs the testbench. |
| `direct_mapped_cache_diagram.pdf`      | Direct-mapped block diagram. |
| `write_port_mux.pdf`                   | Write-port mux detail. |
| `lsu_block_diagram.pdf`                | LSU block diagram. |
| `two_way_cache_diagram.pdf`, `two_way_cache_lsu_diagram.pdf`, `two_way_4word_cache_diagram.pdf`, `lru_block_diagram.pdf` | 2-way / 4-word / LRU diagrams. |
| `devlog/README.md`                      | Dev log index (one entry per stage), plus a PDF version `devlog/cache_diagram_devlog.pdf`. |
| `make_*.py`                            | Python scripts that regenerate the PDFs. |

Run the testbench:

```
./run_cache_tb.sh
```

## Roadmap

### Data cache

| # | Area | Task | Status |
|---|------|------|--------|
| 1 | Design | Direct-mapped (b = 1) block diagram, including LSU and write port | ✅ Done |
| 2 | Design | 2-way set associative (LRU) block diagram, including LSU | ✅ Done |
| 3 | Design | 2-way with 4-word blocks block diagram | ✅ Done |
| 4 | Design | Direct-mapped FSM state diagram finalised (Idle / Read Miss / Write) | ⬜ To do |
| 5 | Direct-mapped RTL | `main_memory.sv` with 32-bit port and `byte_en` (written, not yet committed to `rtl/`) | ⬜ To do |
| 6 | Direct-mapped RTL | `main_memory.sv` unit test (read, write, `byte_en` writes, `mem_ready` pulse) | ⬜ To do |
| 7 | Direct-mapped RTL | `data_cache.sv`: V / tag / data arrays and address split | ⬜ To do |
| 8 | Direct-mapped RTL | `data_cache.sv`: hit logic and read-hit path | ⬜ To do |
| 9 | Direct-mapped RTL | `data_cache.sv`: write port with fill mux and write enable | ⬜ To do |
| 10 | Direct-mapped RTL | `data_cache.sv`: FSM (Idle / Read Miss / Write) and `stall` | ⬜ To do |
| 11 | Direct-mapped RTL | Update `cache_top.sv` to wire LSU, cache and memory | ⬜ To do |
| 12 | Verification | Testbench: read miss, read hit | ⬜ To do |
| 13 | Verification | Testbench: write hit, write miss (no allocate) | ⬜ To do |
| 14 | Verification | Testbench: conflict miss (same set, different tag) | ⬜ To do |
| 15 | Verification | Check waveforms for `stall` timing and `mem_req` / `mem_ready` handshake | ⬜ To do |
| 16 | Integration | Connect to the pipeline MEM stage | ⬜ To do |
| 17 | Integration | Hook `stall` into the hazard unit and freeze the pipeline correctly | ⬜ To do |
| 18 | Integration | Run the reference program with the cache in place | ⬜ To do |
| 19 | Extensions | 2-way set associative RTL with LRU bit per set | ⬜ To do |
| 20 | Extensions | 2-way testbench (victim selection, LRU update) | ⬜ To do |
| 21 | Extensions | 4-word blocks RTL (128-bit memory port, word select mux) | ⬜ To do |
| 22 | Extensions | Compare hit rates of all three designs on the reference program | ⬜ To do |

### LSU

| # | Area | Task | Status |
|---|------|------|--------|
| 1 | Design | LSU block diagram (store path and load path) | ✅ Done |
| 2 | RTL | `lsu.sv`: `byte_en` generation and store data alignment | ⬜ To do |
| 3 | RTL | `lsu.sv`: load byte / half selection with sign and zero extension | ⬜ To do |
| 4 | Verification | Testbench: `lb` / `lh` / `lbu` / `lhu` / `sb` / `sh` through the LSU | ⬜ To do |
