module top (
    input  logic        clk,
    input  logic        rst,
    output logic [31:0] a0
);
    logic [31:0] PC, instr, ImmOp;
    logic RegWrite, ALUsrc, ALUctrl, EQ, PCsrc, ImmSrc;

    Pc_counter PC_inst (
        .clk(clk),
        .rst(rst),
        .ImmOp(ImmOp),
        .PC_out(PC),
        .PCsrc(PCsrc)
    );

    instr_mem imem (
        .addr(PC[8:0]),   // ADDRESS_WIDTH = 9
        .instr(instr)
    );

    reddatapath dp (
        .clk(clk),
        .rs1(instr[19:15]),
        .rs2(instr[24:20]),
        .rd(instr[11:7]),
        .RegWrite(RegWrite),
        .ALUsrc(ALUsrc),
        .ALUctrl(ALUctrl),
        .ImmOp(ImmOp),
        .EQ(EQ),
        .a0(a0)
    );

    control_unit cu (
        .opcode(instr[6:0]),
        .EQ(EQ),
        .RegWrite(RegWrite),
        .ALUctrl(ALUctrl),
        .ALUsrc(ALUsrc),
        .ImmSrc(ImmSrc),
        .PCsrc(PCsrc)
    );

    sign_extend se (
        .ImmSrc(ImmSrc),
        .ImmOp(ImmOp),
        .instr(instr)
    );

endmodule
