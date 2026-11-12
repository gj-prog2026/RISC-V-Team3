module top (
    input  logic        clk,
    input  logic        rst,
    output logic [31:0] a0
);
    logic [31:0] PC, instr, ImmOp;
    logic RegWrite, ALUsrc, ALUctrl, EQ;

instr_mem imem (
    .addr(PC[8:0]),   // ADDRESS_WIDTH = 9
    .instr(instr)
);

reddatapath dp (
    .clk(clk),
    .rs1(instr[19:15]),
    .rs2(instr[24:20]),
    .rd(instr[11:7]),
    .RegWrite(RegWrite), .ALUsrc(ALUsrc), .ALUctrl(ALUctrl),
    .ImmOp(ImmOp),
    .EQ(EQ), .a0(a0)
);

endmodule
