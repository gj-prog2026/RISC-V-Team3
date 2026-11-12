module reddatapath #(
    parameter ADDR_WIDTH = 5,
              DATA_WIDTH = 32
)(
    input  logic                  clk,
    input  logic [ADDR_WIDTH-1:0] rs1, rs2, rd,
    input  logic                  RegWrite,
    input  logic                  ALUsrc,
    input  logic                  ALUctrl,
    input  logic [DATA_WIDTH-1:0] ImmOp,
    output logic                  EQ,
    output logic [DATA_WIDTH-1:0] a0
);
    logic [DATA_WIDTH-1:0] ALUop1, regOp2, ALUop2, ALUout;

    regfile #(ADDR_WIDTH, DATA_WIDTH) rf (
        .clk(clk), .AD1(rs1), .AD2(rs2), .AD3(rd),
        .WE3(RegWrite), .WD3(ALUout),
        .RD1(ALUop1), .RD2(regOp2), .a0(a0)
    );

    mux #(DATA_WIDTH) alu_src_mux (
        .regOp2(regOp2), .ImmOp(ImmOp),
        .ALUsrc(ALUsrc), .ALUop2(ALUop2)
    );

    alu #(DATA_WIDTH) alu_inst (
        .ALUop1(ALUop1), .ALUop2(ALUop2), .ALUctrl(ALUctrl),
        .ALUout(ALUout), .EQ(EQ)
    );
endmodule