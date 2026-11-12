module regfile#(
    parameter ADDR_WIDTH = 5,
              DATA_WIDTH = 32 
)(
    input logic clk,
    input logic [ADDR_WIDTH-1:0] AD1, AD2, AD3,
    input logic WE3,
    input logic [DATA_WIDTH-1:0] WD3,
    output logic [DATA_WIDTH-1:0] RD1, RD2, a0 
);
logic [DATA_WIDTH-1:0] regs[2**ADDR_WIDTH-1:0];
assign RD1 = regs[AD1];
assign RD2 = regs[AD2];
assign a0 = regs[10];

always_ff @(posedge clk) begin
    if (WE3!=0 && AD3!=0)
        regs[AD3] <= WD3;
end 
endmodule
