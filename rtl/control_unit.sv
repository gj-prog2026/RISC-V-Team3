module control_unit #(
    parameter OP_WIDTH = 7
)(
    input logic EQ,
    input logic [OP_WIDTH-1:0] opcode,
    output logic RegWrite,
    output logic ALUctrl,
    output logic ALUsrc,
    output logic Immsrc,
    output logic PCsrc
);

always_comb begin
    // safe defaults
    
    case(opcode)
        // addi instruction
        7'b0010011: begin 
            RegWrite = 1'b1;
            PCsrc = 1'b0;
            Immsrc = 1'b0;
            ALUctrl = 1'b0;
            ALUsrc = 1'b1;
        end
        // bne instruction
        7'b1100011: begin 
            RegWrite = 1'b0;
            PCsrc = ~EQ;
            Immsrc = 1'b1;
            ALUctrl = 1'b1;
            ALUsrc = 1'b0;
        end
        default: begin
            RegWrite = 1'b0;
            ALUctrl = 1'b0;
            ALUsrc = 1'b0;
            Immsrc = 1'b0;
            PCsrc = 1'b0;
        end

    endcase
end

endmodule
