module sign_extend #(
    parameter INSTR_WIDTH = 32,
              IMMOP_WDITH = 32
)(
    input logic ImmSrc,
    /* verilator lint_off UNUSED */
    input logic [INSTR_WIDTH-1:0] instr,
    /* verilator lint_on UNUSED */
    output logic [IMMOP_WDITH-1:0] ImmOp
);

always_comb begin
    if(ImmSrc) ImmOp = {{19{instr[31]}},instr[31], instr[7], instr[30:25], instr[11:8], 1'b0};
    else ImmOp = {{20{instr[31]}}, instr[31:20]};
end

endmodule
