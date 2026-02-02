module light(
  input clk,
  input rst,
  output reg [15:0] led
);
  reg [31:0] key_count;
  always @(posedge clk) begin
    if (rst) begin led <= 31; key_count <= 0; end
    else begin
      if (key_count == 0) led <= {led[14:0], led[15]};
      key_count <= (key_count >= 5000000 ? 32'b0 : key_count + 1);
    end
  end
endmodule
