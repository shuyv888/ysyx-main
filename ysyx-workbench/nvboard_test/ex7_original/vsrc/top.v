module ex7
(
  input ps2_clk,
  input ps2_data,
  input rst,
  output reg[6:0]seg0,
  output reg[6:0]seg1,
  output reg[6:0]seg2,
  output reg[6:0]seg3,
  output reg[6:0]seg4,
  output reg[6:0]seg5
);
  reg [10:0]key;
  reg [3:0]key_count;
  reg data_f0;
  reg [7:0]data;
  reg [7:0]data_count;
  reg key_pressed;

  always @(negedge ps2_clk or posedge rst) begin
    if(rst)begin
      key <=0;
      key_count <=0;
      data_f0 <=0;
      data <=0;
      data_count <=0;
      key_pressed <= 0;
    end
    else begin
      key <= {ps2_data,key[10:1]};
      key_count <= key_count+1;
      if (key_count==11) begin
        key_count <=0;
        if(key[8:1]==8'hF0)begin
          data_f0 <=1;
          key_pressed <=0;
        end
        else begin
          if(data_f0)begin
            data_f0 <=0;

          end
          else begin
            if (!key_pressed)begin
              data <=key[8:1];
              data_count <=data_count+1;
              key_pressed <=1;
            end
          end
        end
      end
    end
  end

  always @(*) begin
    seg0 = 7'b1111111;
    seg1 = 7'b1111111;
    seg2 = 7'b1111111;
    seg3 = 7'b1111111;
    seg4 = 7'b1111111;
    seg5 = 7'b1111111;
    if (data_f0) begin
      seg4 = seg_decode(data_count[3:0]);
      seg5 = seg_decode(data_count[7:4]);
    end
    else begin
      seg0 = seg_decode(data[3:0]);
      seg1 = seg_decode(data[7:4]);
      seg2 = seg_decode(scan2ascii(data)[3:0]);
      seg3 = seg_decode(scan2ascii(data)[7:4]);
      seg4 = seg_decode(data_count[3:0]);
      seg5 = seg_decode(data_count[7:4]);
    end
  end

  function [7:0] scan2ascii;
    input [7:0] in;
    begin
      case(in)
        8'h1C: scan2ascii = 8'h41; // A -> 'A'
        8'h32: scan2ascii = 8'h42; // B -> 'B'
        8'h21: scan2ascii = 8'h43; // C -> 'C'
        8'h23: scan2ascii = 8'h44; // D -> 'D'
        8'h24: scan2ascii = 8'h45; // E -> 'E'
        8'h2B: scan2ascii = 8'h46; // F -> 'F'
        8'h34: scan2ascii = 8'h47; // G -> 'G'
        8'h33: scan2ascii = 8'h48; // H -> 'H'
        8'h43: scan2ascii = 8'h49; // I -> 'I'
        8'h3B: scan2ascii = 8'h4A; // J -> 'J'
        8'h42: scan2ascii = 8'h4B; // K -> 'K'
        8'h4B: scan2ascii = 8'h4C; // L -> 'L'
        8'h3A: scan2ascii = 8'h4D; // M -> 'M'
        8'h31: scan2ascii = 8'h4E; // N -> 'N'
        8'h44: scan2ascii = 8'h4F; // O -> 'O'
        8'h4D: scan2ascii = 8'h50; // P -> 'P'
        8'h15: scan2ascii = 8'h51; // Q -> 'Q'
        8'h2D: scan2ascii = 8'h52; // R -> 'R'
        8'h1B: scan2ascii = 8'h53; // S -> 'S'
        8'h2C: scan2ascii = 8'h54; // T -> 'T'
        8'h3C: scan2ascii = 8'h55; // U -> 'U'
        8'h2A: scan2ascii = 8'h56; // V -> 'V'
        8'h1D: scan2ascii = 8'h57; // W -> 'W'
        8'h22: scan2ascii = 8'h58; // X -> 'X'
        8'h35: scan2ascii = 8'h59; // Y -> 'Y'
        8'h1A: scan2ascii = 8'h5A; // Z -> 'Z'
        8'h45: scan2ascii = 8'h30; // 0 -> '0'
        8'h16: scan2ascii = 8'h31; // 1 -> '1'
        8'h1E: scan2ascii = 8'h32; // 2 -> '2'
        8'h26: scan2ascii = 8'h33; // 3 -> '3'
        8'h25: scan2ascii = 8'h34; // 4 -> '4'
        8'h2E: scan2ascii = 8'h35; // 5 -> '5'
        8'h36: scan2ascii = 8'h36; // 6 -> '6'
        8'h3D: scan2ascii = 8'h37; // 7 -> '7'
        8'h3E: scan2ascii = 8'h38; // 8 -> '8'
        8'h46: scan2ascii = 8'h39; // 9 -> '9'
        default: scan2ascii = 8'hff;
      endcase
    end
  endfunction
  function [6:0] seg_decode;
    input [3:0] in;
    begin
      case(in)
        4'h0: seg_decode = 7'b0000001; // 0
        4'h1: seg_decode = 7'b1001111; // 1
        4'h2: seg_decode = 7'b0010010; // 2
        4'h3: seg_decode = 7'b0000110; // 3
        4'h4: seg_decode = 7'b1001100; // 4
        4'h5: seg_decode = 7'b0100100; // 5
        4'h6: seg_decode = 7'b0100000; // 6
        4'h7: seg_decode = 7'b0001111; // 7
        4'h8: seg_decode = 7'b0000000; // 8
        4'h9: seg_decode = 7'b0000100; // 9
        4'hA: seg_decode = 7'b0001000; // A
        4'hB: seg_decode = 7'b1100000; // B
        4'hC: seg_decode = 7'b0110000; // C
        4'hD: seg_decode = 7'b1000010; // D
        4'hE: seg_decode = 7'b0110000; // E
        4'hF: seg_decode = 7'b0111000; // F
        default: seg_decode = 7'b1111111;
      endcase
    end
  endfunction

endmodule