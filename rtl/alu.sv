module alu #(
    parameter WIDTH = 32
)(
    input  logic [WIDTH-1:0] ALUop1, ALUop2,
    input  logic             ALUctrl,
    output logic [WIDTH-1:0] ALUout,
    output logic             EQ
);
    always_comb begin
        case (ALUctrl)
            1'b0:    ALUout = ALUop1 + ALUop2;           // addi
            1'b1:    ALUout = ALUop1 + ~ALUop2 + 1'b1;   // bne
            default: ALUout = '0;
        endcase
    end

    assign EQ = (ALUout == '0); 
endmodule