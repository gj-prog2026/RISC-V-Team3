module Pc_counter #(
    parameter RESET_PC = 32'h0
)(
    input logic clk,
    input logic rst,
    input logic PCsrc,
    input logic[31:0] ImmOp,
    output logic[31:0] PC_out
);
    logic [31:0] pc_reg = RESET_PC;
    logic [31:0] pc_inc;
    logic [31:0] pc_branch;
    logic [31:0] pc_next;

    always_ff @(posedge clk)
        if(rst) pc_reg <= RESET_PC;
        else pc_reg <= pc_next; 

    always_comb begin
        pc_branch = pc_reg + ImmOp;
    end

    always_comb begin
        pc_inc = pc_reg + 32'h4;
    end

    assign pc_next = PCsrc ? pc_branch : pc_inc;
    assign PC_out = pc_reg;

endmodule
