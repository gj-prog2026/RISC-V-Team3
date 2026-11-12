module top #(
    DATA_WIDTH = 32
) (
    input   logic clk,
    input   logic rst,
    output  logic [DATA_WIDTH-1:0] a0    
);
    assign a0 = 32'd5;

    logic[31:0] ImmOp;
    logic[31:0] PC_out;
    logic PCsrc;

    Pc_counter PC_inst(
        .clk(clk),
        .rst(rst),
        .ImmOp(ImmOp),
        .PC_out(PC_out),
        .PCsrc(PCsrc)
    );

endmodule
