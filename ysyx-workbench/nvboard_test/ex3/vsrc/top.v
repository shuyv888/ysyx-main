module ex3(
	input [7:0] in,
	input [2:0] mode,
	output reg [3:0] out,
	output reg zf,
	output reg of,
	output reg cf
);  
	wire [3:0] a = in[3:0];
	wire [3:0] b = in[7:4];
	
	always @(*) begin
		zf = 0;
		of = 0;
		cf = 0;
		out = 0;
		case(mode)
			3'b000: begin
				out = a + b;
				zf = (out == 0);
				of = (~a[3] & ~b[3] & out[3]) | (a[3] & b[3] & ~out[3]);
				cf = a[3] ^ b[3];
			end
			3'b001: begin
				out = a + b;
				zf = (out == 0);
				of = (~a[3] & ~b[3] & out[3]) | (a[3] & b[3] & ~out[3]);
				cf = a[3] ^ b[3];
			end
			3'b010: begin
				out = ~a;
			end
			3'b011: begin
				out = a & b;
			end
			3'b100: begin
				out = a | b;
			end
			3'b101: begin
				out = a ^ b;
			end
			3'b110: begin
 				out = {3'b000, (a[3] & ~b[3]) | ((a[3] == b[3]) & (a < b))};
			end
            		3'b111: begin
				out = {3'b000, (a == b)};
			end
		endcase
	end
endmodule
