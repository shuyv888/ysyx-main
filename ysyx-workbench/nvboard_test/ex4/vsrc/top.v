module ex4(
	input clk,
	input rst,
	input stop,
	output reg [6:0]hex0,
	output reg [6:0]hex1,
	output reg led
);
	reg [24:0] count_clk;
	reg [7:0] count_clk_1s;
	reg stp;
	reg clk_1s;
	reg [3:0] tens ,units;
	initial begin
		
	end
	always @(posedge clk or posedge rst) begin
		if(rst) begin
			count_clk <=0;
			clk_1s <=0;
		end
		else begin
			if(count_clk==24999999) begin
				count_clk <=0;
				clk_1s <= ~clk_1s;
			end
			else begin
				count_clk <= count_clk+1;
			end
		end
	end
	always @(posedge clk_1s or posedge rst)begin
		if(rst) begin
			count_clk_1s <=0;
		end
		else begin
			if(count_clk_1s ==99) begin
				count_clk_1s <=0;
				led <= 1;
			end
			else begin
				count_clk_1s <=count_clk_1s+1;
				led <= 0;
			end
			if(stop) begin
				stp<=~stp;
			end
			if (stp) begin
				tens <= (count_clk_1s/10)[3:0];
				units <=(count_clk_1s%10)[3:0];
				case(tens)
					0: hex1 <= 7'b1000000;
					1: hex1 <= 7'b1111001;
					2: hex1 <= 7'b0100100;
					3: hex1 <= 7'b0110000;
					4: hex1 <= 7'b0011001;
					5: hex1 <= 7'b0010010;
					6: hex1 <= 7'b0000010;
					7: hex1 <= 7'b1111000;
					8: hex1 <= 7'b0000000;
					9: hex1 <= 7'b0010000;
					default: hex1 <= 7'b1111111;
				endcase
				case(units)
					0: hex0 <= 7'b1000000;
					1: hex0 <= 7'b1111001;
					2: hex0 <= 7'b0100100;
					3: hex0 <= 7'b0110000;
					4: hex0 <= 7'b0011001;
					5: hex0 <= 7'b0010010;
					6: hex0 <= 7'b0000010;
					7: hex0 <= 7'b1111000;
					8: hex0 <= 7'b0000000;
					9: hex0 <= 7'b0010000;
					default: hex0 <= 7'b1111111;
				endcase
			end
			else begin
				hex0 <=hex0;
				hex1 <=hex1;
			end
		end
	end
endmodule
