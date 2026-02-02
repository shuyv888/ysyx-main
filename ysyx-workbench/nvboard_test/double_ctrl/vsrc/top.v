module top(
	input clk,
	input rst,
	input [1:0] sw,
	output status
);
	assign status = sw[1]^sw[0];
endmodule
