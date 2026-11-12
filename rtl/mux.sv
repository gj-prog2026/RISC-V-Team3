module mux#(
    parameter WIDTH = 32
)(
    input logic [WIDTH-1:0] regOp2, ImmOp,
    input logic ALUsrc,
    output logic [WIDTH-1:0] ALUop2
);
    always_comb begin
        case (ALUsrc)
            1'b1: ALUop2 = ImmOp;
            default: ALUop2 = regOp2;
        endcase
    end
endmodule
