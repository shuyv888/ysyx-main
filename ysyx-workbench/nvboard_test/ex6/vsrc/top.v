module ex6(
	input [7:0]in,
	input clk,
	input updata,
	input rst,
	output reg [6:0]hex0,
	output reg [6:0]hex1,
	output reg [6:0]hex2,
	output reg [6:0]hex3,
	output reg [6:0]hex4,
	output reg [6:0]hex5,
	output reg [6:0]hex6,
	output reg [6:0]hex7
);
	reg [7:0] data;

	always@(posedge clk or posedge rst) begin
		if(rst) begin
			data <=8'b0;
			hex0 <= 7'b0000000;
			hex1 <= 7'b0000000;
			hex2 <= 7'b0000000;
			hex3 <= 7'b0000000;
			hex4 <= 7'b0000000;
			hex5 <= 7'b0000000;
			hex6 <= 7'b0000000;
			hex7 <= 7'b0000000;
		end 
		else begin
			if(updata==1) begin
				if (in==0) begin
					data <=8'b00000001;
				end
				else begin
					data <= in;
				end
			end
			else begin
				data <={data[4]^data[3]^data[2]^data[0],data[7:1]};
				hex0 <= data[0] ? 7'b1111001 : 7'b1000000;
				hex1 <= data[1] ? 7'b1111001 : 7'b1000000;
				hex2 <= data[2] ? 7'b1111001 : 7'b1000000;
				hex3 <= data[3] ? 7'b1111001 : 7'b1000000;
				hex4 <= data[4] ? 7'b1111001 : 7'b1000000;
				hex5 <= data[5] ? 7'b1111001 : 7'b1000000;
				hex6 <= data[6] ? 7'b1111001 : 7'b1000000;
				hex7 <= data[7] ? 7'b1111001 : 7'b1000000;
			end
		end		
	end
endmodule
