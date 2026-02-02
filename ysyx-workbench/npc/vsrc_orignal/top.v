module top (
  input clk,
  // 原本的指令读取
  input [31:0]inst,
  input rst,
  output reg[31:0] pc,
  output reg is_ebreak,
  output wire [31:0]a0,
  output reg illegal_instruction
);

////IFU - 取指
//在main里取了



////IDU - 准备需要的数据和控制信号
//函数声明
  import "DPI-C" function void print_halt(input int pc_value);
  import "DPI-C" function int pmem_read(input int raddr);
  import "DPI-C" function void pmem_write(
    input int mem_waddr, input int mem_wdata, input byte mem_wmask);


  reg [31:0] pc_reg;    //pc
  wire [31:0] pc_dnpc;   //pc候选
  reg wen;
  reg is_add, is_addi, is_lui, is_lw, is_lbu, is_sw, is_sb, is_jalr, is_auipc, is_csrrw;         //寄存器数据写入选择,八位数据每位代表一种指令选择
  reg [4:0] rs1_addr,rs2_addr;
  reg [4:0] rd_addr;
  reg [31:0] imm;
  wire [31:0] wdata;
  //各指令写入寄存器的数据
  wire [31:0] wdata_add, wdata_addi, wdata_lui, wdata_lw, wdata_lbu, wdata_jalr, wdata_auipc, wdata_csrrw;
  wire [31:0] rs1_data, rs2_data;     
  wire [31:0] jalr_pc_out;  // jalr模块输出的新PC
  assign wdata  = is_add   ? wdata_add  :
                  is_addi  ? wdata_addi :
                  is_lui   ? wdata_lui  :
                  is_lw    ? wdata_lw   :
                  is_lbu   ? wdata_lbu  :
                  is_jalr  ? wdata_jalr :
                  is_auipc ? wdata_auipc:
                  is_csrrw ? wdata_csrrw:
                  32'd0;  
// CSR指令写回数据直接取CSR读出值
assign wdata_csrrw = csr_rdata;


//LSU的配置
  reg [31:0] mem_raddr;
  wire [31:0] mem_wdata;
  wire [31:0] mem_wdata_sw, mem_wdata_sb;
  reg [31:0] mem_waddr;
  reg [3:0] mem_wmask;
  reg mem_valid;
  reg mem_wen;
  reg [31:0] mem_rdata;//这里改成reg了

  assign mem_wdata  = is_sw ?  mem_wdata_sw:
                      is_sb ?  mem_wdata_sb:
                      32'd0;

  assign pc = pc_reg;
//使用组合逻辑通过inst判断是否跳转
  assign pc_dnpc = (inst[6:0] == 7'b1100111) ? jalr_pc_out : (pc_reg + 4);


////WBU写入和更新pc?
  always @(posedge clk) begin
    if (rst) begin
      pc_reg <= 32'h80000000;  //复位时PC清零
    end else begin
      if (mem_valid) begin // 有读写请求时
        if (mem_wen) begin // 有写请求时
          pmem_write(mem_waddr, mem_wdata, mem_wmask);
        end
      end
      pc_reg <= pc_dnpc;  //时钟沿更新PC值
    end
  end

//内存读写，LSU
  always @(*) begin
    if (mem_valid) begin // 有读写请求时
      mem_rdata = pmem_read(mem_raddr);
    end
    else begin
      mem_rdata = 0;
    end
  end


////感觉像EXU？感觉要加个是否输出
//模块实例
  add u_add (
    .rs1(rs1_data),
    .rs2(rs2_data),  // 连接rs2数据
    .is_add(is_add),
    .out(wdata_add)
  );
  addi u_addi (
    .rs1(rs1_data),
    .imm(imm),
    .is_addi(is_addi),
    .out(wdata_addi)
  );

  
  lui u_lui(
    .imm(imm),
    .is_lui(is_lui),
    .out(wdata_lui)
  );


  lw u_lw(
    .mem_rdata(mem_rdata),
    .is_lw(is_lw),
    .out(wdata_lw)
  );

  lbu u_lbu(
    .mem_rdata(mem_rdata),
    .mem_raddr(mem_raddr),
    .is_lbu(is_lbu),
    .out(wdata_lbu)
  );

  sw u_sw(
    .rs2(rs2_data),
    .is_sw(is_sw),
    .out(mem_wdata_sw)
  );

  sb u_sb(
    .rs2(rs2_data),
    .is_sb(is_sb),
    .out(mem_wdata_sb)
  );

  jalr u_jalr(
    .pc_reg(pc_reg),
    .imm(imm),
    .rs1(rs1_data),
    // .is_jalr(is_jalr),
    .pc_out(jalr_pc_out),
    .out(wdata_jalr)
  );

  auipc u_auipc (
    .pc_reg(pc_reg),
    .imm(imm),
    .is_auipc(is_auipc), 
    .out(wdata_auipc)
  );

  RegisterFile #(
    .ADDR_WIDTH(5),
    .DATA_WIDTH(32)
  ) gpr (
    .clk(clk),
    .wdata(wdata),
    .waddr(rd_addr),        
    .wen(wen),
    .raddr1(rs1_addr), 
    .raddr2(rs2_addr),
    .rdata1(rs1_data),
    .rdata2(rs2_data),
    .a0(a0)
  );

  csr u_csr (
    .clk(clk),
    .rst(rst),
    .csr_addr(inst[31:20]),  // 从指令中提取CSR地址
    .rs1_data(rs1_data),    // 使用rs1的值作为写入数据
    .csrrw_en(is_csrrw),  // 判断是否为csrrw指令
    .rd_data(csr_rdata)        // 添加csr_rdata信号
  );


////IDU - 译码单元
  
  always @(*) begin
  
    wen = 0;
    rs1_addr = 5'd0;
    rs2_addr = 5'd0;
    rd_addr = 5'd0;
    imm = 32'd0;
    {is_add, is_addi, is_lui, is_lw, is_lbu, is_sw, is_sb, is_jalr, is_auipc} <= 9'b0;
    mem_valid = 0;
    mem_wen = 0;

    is_ebreak = 0; // 默认不是 ebreak
    illegal_instruction = 0; // 默认不是非法指令
    
    if (!rst) begin
      casez (inst)
        //1. add
        32'b0000000_?????_?????_000_?????_01100_11: begin 
          wen = 1;
          rs1_addr = inst[19:15];
          rs2_addr = inst[24:20];
          rd_addr = inst[11:7];
          is_add = 1;
        end

        //2. addi
        32'b???????_?????_?????_000_?????_00100_11: begin 
          wen = 1;
          rs1_addr = inst[19:15];
          rd_addr = inst[11:7];
          imm = {{20{inst[31]}}, inst[31:20]};
          is_addi = 1;
        end
        
        //3. lui
        32'b???????_?????_?????_???_?????_01101_11: begin
          wen = 1;
          rd_addr = inst[11:7];
          imm = {inst[31:12],12'b0};
          is_lui = 1;
        end

        //4. lw 
        //从地址 x[rs1] + sign-extend(offset) 读取 4 字节，写入 x[rd]。
        32'b???????_?????_?????_010_?????_00000_11: begin
          wen = 1;
          mem_valid = 1;
          rs1_addr = inst[19:15];
          imm = {{20{inst[31]}}, inst[31:20]};
          mem_raddr = rs1_data + imm;
          rd_addr = inst[11:7];
          is_lw = 1;
        end


        //5. lbu
        //从地址 x[rs1] + sign-extend(offset) 读取 1 字节，零扩展后写入 x[rd]。
        32'b???????_?????_?????_100_?????_00000_11: begin
          wen =1;
          mem_valid = 1;
          rs1_addr = inst[19:15];
          imm = {{20{inst[31]}}, inst[31:20]};
          mem_raddr = rs1_data +imm;
          rd_addr = inst[11:7];
          is_lbu = 1;

        end


        //6. sw
        //将 x[rs2] 的最低 4 字节写入内存地址 x[rs1]+sign-extend(offset)
        32'b???????_?????_?????_010_?????_01000_11: begin
          mem_wen = 1;
          mem_valid = 1;
          rs1_addr = inst[19:15];
          rs2_addr = inst[24:20];
          imm = {{20{inst[31]}},inst[31:25],inst[11:7]};
          mem_waddr = rs1_data + imm;
          mem_wmask = 4'b1111;
          is_sw = 1;
        end


        //7. sb
        //将 x[rs2] 的最低字节写入内存地址 x[rs1]+sign-extend(offset)。
        32'b???????_?????_?????_000_?????_01000_11: begin
          mem_wen = 1;
          mem_valid = 1;
          rs1_addr = inst[19:15];
          rs2_addr = inst[24:20];
          imm = {{20{inst[31]}},inst[31:25],inst[11:7]};
          mem_waddr = rs1_data + imm;
          mem_wmask = 1 << (mem_waddr[1:0]);
          is_sb = 1;
        end

        //8. jalr
        32'b???????_?????_?????_000_?????_11001_11: begin 
          wen = 1;
          rs1_addr = inst[19:15];
          rd_addr = inst[11:7];
          imm = {{20{inst[31]}}, inst[31:20]};
          is_jalr = 1;
        end

        //9. auipc
        32'b???????_?????_?????_???_?????_00101_11: begin 
          wen = 1;
          rd_addr = inst[11:7];
          imm = {inst[31:12], 12'b0};
          is_auipc = 1;
        end

        //csrrw
        32'b???????_?????_?????_001_?????_11100_11: begin
          wen = 1;
          rs1_addr = inst[19:15];
          rd_addr = inst[11:7];
          is_csrrw = 1;
        end

        //ebrak
        32'b0000000_00001_00000_000_00000_11100_11: begin
          is_ebreak = 1;
        end
        
        
        default: begin
          is_ebreak = (inst == 0) ?  0 : 1;
          illegal_instruction = (inst == 0) ?  0 : 1;
        end
      endcase
    end
  end




endmodule


////下方为各模块，应该是EXU

module add (
  input [31:0] rs1,
  input [31:0] rs2,

  
  input is_add,
  output [31:0] out
);
  assign  out = is_add ? (rs1 + rs2) : 32'd0;
endmodule

module addi (
  input [31:0] rs1,
  input [31:0] imm,
  input is_addi,
  output [31:0] out
);
  assign  out = is_addi ? (rs1 + imm) : 32'd0;
endmodule

module lui (
  input [31:0] imm,    // 20位立即数（inst[31:12]）
  input is_lui,
  output [31:0] out
);
  assign out = is_lui ? imm : 32'd0;  // 高20位为立即数，低12位补0
endmodule

module lw (
  input [31:0] mem_rdata,
  input is_lw,
  output [31:0] out
);
  assign out = is_lw ? mem_rdata : 32'd0;
endmodule

module lbu (
  input [31:0] mem_rdata,
  input [31:0] mem_raddr,
  input is_lbu,
  output [31:0] out
);
  reg [7:0] lbu_byte;

  always @(*) begin
    case (mem_raddr[1:0])
      2'b00: lbu_byte = mem_rdata[7:0];
      2'b01: lbu_byte = mem_rdata[15:8];
      2'b10: lbu_byte = mem_rdata[23:16];
      2'b11: lbu_byte = mem_rdata[31:24];
      default: lbu_byte = 8'd0;
    endcase
  end
  assign out = is_lbu ? {24'b0, lbu_byte} : 32'd0;
endmodule

module sw (
  input [31:0] rs2,
  input is_sw,
  output [31:0] out
);
  assign out = is_sw ? rs2 : 32'b0;
endmodule

module sb (
  input [31:0] rs2,
  input is_sb,
  output [31:0] out
);
  assign out = is_sb ? rs2 & 32'h000000FF : 32'b0;
endmodule

module jalr (
  input [31:0] pc_reg,
  input [31:0] imm,
  input [31:0] rs1,
  output [31:0] pc_out,
  output [31:0] out
);
  assign out = pc_reg + 4;
  assign pc_out = ((rs1 + imm) & 32'hFFFFFFFE);
endmodule

module auipc (
  input [31:0] pc_reg,
  input [31:0] imm,
  input is_auipc,
  output [31:0] out
);
  assign out = is_auipc ? (pc_reg + imm) : 32'd0;
endmodule

module RegisterFile #(ADDR_WIDTH = 1, DATA_WIDTH = 1) (
  input clk,
  input [DATA_WIDTH-1:0] wdata,
  input [ADDR_WIDTH-1:0] waddr,
  input wen,
  input [ADDR_WIDTH-1:0] raddr1,
  input [ADDR_WIDTH-1:0] raddr2,
  output [DATA_WIDTH-1:0] rdata1,
  output [DATA_WIDTH-1:0] rdata2,

  output [DATA_WIDTH-1:0] a0
);
  reg [DATA_WIDTH-1:0] rf [2**ADDR_WIDTH-1:0];
  always @(posedge clk) begin
    if (wen && (waddr != 0)) rf[waddr] <= wdata;//虽然讲义说不要改，但我还是改了
  end
  assign rdata1 = (raddr1 == 0) ? 0 : rf[raddr1];
  assign rdata2 = (raddr2 == 0) ? 0 : rf[raddr2];//yi

  assign a0 = rf[10];//专门给a0调了一个
endmodule

module csr (
  input clk,
  input rst,
  input [11:0] csr_addr,
  input [31:0] rs1_data,
  input csrrw_en,
  output reg [31:0] rd_data
);
// 定义需要的CSR寄存器
reg [31:0] mcycle;    // 机器周期计数（低32位）
reg [31:0] mcycleh;   // 机器周期计数（高32位）
reg [31:0] mvendorid; // 厂商ID（只读）
reg [31:0] marchid;   // 架构ID（只读）

wire [63:0] mcycle_total;
assign mcycle_total = {mcycleh, mcycle};

//// 1. 周期计数更新（时序逻辑：仅用非阻塞赋值）
always @(posedge clk or posedge rst) begin
  if (rst) begin
    mcycle  <= 32'h00000000;
    mcycleh <= 32'h00000000;
  end else begin
    // 优先处理CSRRW写操作，否则正常计数
    if (csrrw_en && (csr_addr == 12'hb00)) begin
      mcycle <= rs1_data;  // CSRRW写mcycle
    end else if (csrrw_en && (csr_addr == 12'hb80)) begin
      mcycleh <= rs1_data; // CSRRW写mcycleh
    end else begin
      {mcycleh, mcycle} <= mcycle_total + 64'h1;  // 正常计数
    end
  end
end

//// 2. 只读CSR初始化（复位时）
always @(posedge rst) begin
  if (rst) begin
    mvendorid <= 32'h79737978;  // 自定义厂商ID
    marchid   <= 32'h017eb18f;  // 自定义架构ID
  end
end

//// 3. CSR读操作（组合逻辑：仅读，不写）
always @(*) begin
  case (csr_addr)
    12'hb00: rd_data = mcycle;    // 读mcycle
    12'hb80: rd_data = mcycleh;   // 读mcycleh
    12'hf11: rd_data = mvendorid; // 读mvendorid
    12'hf12: rd_data = marchid;   // 读marchid
    default: rd_data = 32'h00000000;  // 未定义CSR读0
  endcase
end

endmodule
// module csr (
//     input clk,
//     input rst,
//     input wire [11:0] csr_addr,
//     input wire [31:0] rs1_data,
//     input wire csrrw_en,
//     output reg [31:0] rd_data
// );
// reg [31:0] mcycle;
// reg [31:0] mcycleh;
// reg [31:0] mvendorid;
// reg [31:0] marchid;

// wire [63:0] mcycle_total;
// assign mcycle_total = {mcycleh, mcycle};

// always @(posedge clk or posedge rst) begin
//     if (rst) begin
//         mcycle  <= 32'h0;
//         mcycleh <= 32'h0;
//     end else begin
//         {mcycleh, mcycle} <= mcycle_total + 64'h1;
//     end
// end

// always @(posedge rst) begin
//     if (rst) begin
//         mvendorid <= 32'h79737978;
//         marchid   <= 32'h017eb18f;
//     end
// end
// always @(*) begin
//     // 默认读出0（未定义的CSR）
//     rd_data = 32'h0;
    
//     // 仅在csrrw指令使能时处理
//     if (csrrw_en) begin
//         case (csr_addr)
//             // 处理mcycle（可读写）
//             12'hb00: begin
//                 rd_data = mcycle;               // 读：输出当前mcycle值到rd
//                 mcycle  = rs1_data;             // 写：用rs1的值更新mcycle
//             end
            
//             // 处理mcycleh（可读写）
//             12'hb80: begin
//                 rd_data = mcycleh;              // 读：输出当前mcycleh值到rd
//                 mcycleh = rs1_data;             // 写：用rs1的值更新mcycleh
//             end
            
//             // 处理mvendorid（只读，写操作无效）
//             12'hf11: begin
//                 rd_data = mvendorid;            // 读：输出固定值到rd
//                 // 写操作被忽略（保持只读特性）
//             end
      
//             // 处理marchid（只读，写操作无效）
//             12'hf12: begin
//                 rd_data = marchid;              // 读：输出固定值到rd
//                 // 写操作被忽略
//             end
            
//             // 未定义的CSR
//             default: begin
//                 rd_data = 32'h0;                // 读：输出0
//                 // 写操作无效
//             end
//         endcase
//     end
// end
// endmodule