/*
IDU(Instruction Decode Unit): 
负责对当前指令进行译码, 准备执行阶段需要使用的数据和控制信号
*/
module idu (
  input               rst,        // 复位信号（控制指令解码是否有效）
  input       [31:0]  inst,       // 输入的指令
  input       [31:0]  rs1_data,   // 寄存器rs1的数据（用于计算内存地址）
  
  // 寄存器读写控制
  output reg          wen,        // 寄存器写使能
  output reg  [4:0]   rs1_addr,   // rs1寄存器地址
  output reg  [4:0]   rs2_addr,   // rs2寄存器地址
  output reg  [4:0]   rd_addr,    // rd寄存器地址
  output reg  [4:0]   csr_addr,   // CSR寄存器地址
  
  // 立即数输出
  output reg  [31:0]  imm,        // 解码得到的立即数
  
  // 指令类型标志（控制后续执行阶段）
  output reg          is_add,     // ADD指令标志
  output reg          is_addi,    // ADDI指令标志
  output reg          is_lui,     // LUI指令标志
  output reg          is_lw,      // LW指令标志
  output reg          is_lbu,     // LBU指令标志
  output reg          is_sw,      // SW指令标志
  output reg          is_sb,      // SB指令标志
  output reg          is_jalr,    // JALR指令标志
  output reg          is_auipc,   // AUIPC指令标志
  output reg          is_csrrw,   // CSRRW指令标志
  
  // 内存访问控制
  output reg          mem_valid,  // 内存访问有效标志
  output reg          mem_wen,    // 内存写使能（1为写，0为读）
  output reg  [31:0]  mem_raddr,  // 内存读地址
  output reg  [31:0]  mem_waddr,  // 内存写地址
  output reg  [3:0]   mem_wmask,  // 内存写掩码（字节使能）
  
  // 异常相关标志
  output reg          is_ebreak,          // EBreak指令标志
  output reg          illegal_instruction // 非法指令标志
);  
  always @(*) begin
    wen = 0;
    rs1_addr = 5'd0;
    rs2_addr = 5'd0;
    rd_addr = 5'd0;
    csr_addr = 5'd0;
    imm = 32'd0;
    {is_add, is_addi, is_lui, is_lw, is_lbu, is_sw, is_sb, is_jalr, is_auipc, is_csrrw} = 10'b0;
    mem_valid = 0;
    mem_wen = 0;

    mem_raddr = 32'd0;
    mem_waddr = 32'd0;
    mem_wmask = 4'b0000;

    is_ebreak = 0;
    illegal_instruction = 0;

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
        32'b???????_?????_?????_010_?????_00000_11: begin
          wen = 1;
          mem_valid = 1;
          rs1_addr = inst[19:15];
          imm = {{20{inst[31]}}, inst[31:20]};
          mem_raddr = rs1_data + imm;
          rd_addr = inst[11:7];
          is_lw = 1;
        end

        //5. addi
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

        //10. csrrw
        32'b???????_?????_?????_001_?????_11100_11: begin
          wen = 1;
          csr_addr = inst[19:15];
          rd_addr = inst[11:7];
          is_csrrw = 1;
        end

        //ebreak
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


