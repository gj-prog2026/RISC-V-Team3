module alu#(
    parameter WIDTH = 32
)(
    input logic [WIDTH-1:0] ALUop1, ALUop2,
    input logic ALUctrl,
    output logic [WIDTH-1:0] ALUout,
    output logic EQ //checking if the registers are equal or not
    //brnach taken when the registers are different
);
    always_comb begin
        case (ALUctrl)
            1'b0: ALUout = ALUop1 + ALUop2;
            default: ALUout = '0;
        endcase
    end
    assign EQ = (ALUop1 == ALUop2);
endmodule
