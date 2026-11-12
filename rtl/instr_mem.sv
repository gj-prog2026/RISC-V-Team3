module instr_mem #(
    parameter BYTE_WIDTH = 8,
              ADDRESS_WIDTH = 9,
              INSTR_WIDTH = 32
)(
    input logic [ADDRESS_WIDTH-1:0] addr,
    output logic [INSTR_WIDTH-1:0] instr
);

logic [BYTE_WIDTH-1:0] mem_array [2**ADDRESS_WIDTH-1:0];

initial begin
    $display("Loading rom.");
    $readmemh("tests/test_instr_bytes.mem", mem_array);
end

always_comb begin
    instr = {mem_array[addr+ 3], mem_array[addr+2], mem_array[addr+1], mem_array[addr]};
end

endmodule
