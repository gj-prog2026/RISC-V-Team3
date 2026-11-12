#!/bin/bash
set -e
cd "$(dirname "$0")"
rm -rf obj_dir

verilator -Wall --trace --cc rtl/instr_mem.sv \
    --exe tests/verify_instr_mem.cpp \
    --top-module instr_mem \
    -CFLAGS "-std=c++17" \
    -LDFLAGS "-lgtest -lpthread" \
    --build -j 4

# Run from tests/ so $readmemh can find instruction.mem
obj_dir/Vinstr_mem