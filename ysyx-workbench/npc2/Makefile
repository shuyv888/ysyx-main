VERILATOR = verilator
# 关键选项：指定顶层模块为am，允许警告不终止，开启多线程编译
VERILATOR_FLAGS = -Wall -j 0 --cc --exe --trace --build \
--top-module top \
--Mdir obj_dir \
-Wno-fatal 
# 允许警告（避免非致命警告终止编译）

#trace相关控制
TRACE_FLAGS :=
TRACE_FLAGS += -DITRACE    # 开启指令跟踪（注释此行则关闭）
TRACE_FLAGS += -DMTRACE    # 开启访存跟踪（注释此行则关闭）
# ==========================================================================


# ====================== capstone路径 ======================
# 方式1：绝对路径（推荐，避免目录切换导致路径错误）
LIBCAPSTONE = /home/shuyv/ysyx-workbench/nemu/tools/capstone/repo/libcapstone.so.5
CAPSTONE_INC = -I /home/shuyv/ysyx-workbench/nemu/tools/capstone/repo/include
# 链接时指定capstone库的绝对路径（或用-L指定库目录+ -lcapstone）
CAPSTONE_LD = -L /home/shuyv/ysyx-workbench/nemu/tools/capstone/repo -lcapstone



#传递capstone和trace相关参数给Verilator
# 1. 把capstone的包含路径和trace标志传给C++编译器
VERILATOR_FLAGS += -CFLAGS "$(CAPSTONE_INC) $(TRACE_FLAGS)" 
# 2. 把TRACE_FLAGS转换为Verilog宏（-DITRACE → +define+ITRACE），传给V端
VERILATOR_FLAGS += $(foreach flag,$(TRACE_FLAGS),+define+$(subst -D,,$(flag)))
# 3. 保留原有capstone链接参数
VERILATOR_FLAGS += -LDFLAGS "$(CAPSTONE_LD)"

# =====================================================================

# 文件路径配置
VERILOG_SRC = vsrc/*.v      # Verilog源文件路径
CPP_SRC = csrc_sdb/*.cpp        # C++测试文件路径
C_SRC = csrc_sdb/*.c

EXE = obj_dir/Vtop             # Verilator生成的可执行文件（因文件名为top.v，生成Vtop）
WAVE_FILE = sim/wave_top.vcd    # 波形文件路径
WAVE_FILE_LAYOUT = wave_layout/wave_config.gtkw #展开初始化


# 构建目标
all: run wave


# ====================== capstone库的构建规则 ======================
# 构建capstone库：进入nemu下的capstone目录编译
$(LIBCAPSTONE):
	$(MAKE) -C /home/shuyv/ysyx-workbench/nemu/tools/capstone
	# 若用相对路径则改为：$(MAKE) -C ../nemu/tools/capstone
# ==================================================================

# 编译并运行仿真
run: $(LIBCAPSTONE)
	mkdir -p sim                  # 创建仿真输出目录
	$(VERILATOR) $(VERILATOR_FLAGS) $(VERILOG_SRC) $(CPP_SRC) $(C_SRC) # 编译
	./$(EXE)                      # 运行仿真
#run:
#	mkdir -p sim                  # 创建仿真输出目录
#	$(VERILATOR) $(VERILATOR_FLAGS) $(VERILOG_SRC) $(CPP_SRC) $(C_SRC) # 编译
#	./$(EXE)                      # 运行仿真


# 查看波形
wave:
	@if [ -f $(WAVE_FILE) ]; then \
		gtkwave $(WAVE_FILE) $(WAVE_FILE_LAYOUT); \
	else \
		echo "Error: 波形文件 $(WAVE_FILE) 不存在，请先运行仿真"; \
	fi

# 清理编译产物
clean:
	rm -rf obj_dir sim ./*.vcd
	rm -f $(EXE)
# 可选：清理nemu下的capstone编译产物
# $(MAKE) -C /home/shuyv/ysyx-workbench/nemu/tools/capstone clean
# 相对路径版：$(MAKE) -C ../nemu/tools/capstone clean

# 伪目标声明
.PHONY: all run wave clean

# VERILATOR = verilator
# # 关键选项：指定顶层模块为am，允许警告不终止，开启多线程编译
# VERILATOR_FLAGS = -Wall -j 0 --cc --exe --trace --build \
# --top-module top \
# --Mdir obj_dir \
# -Wno-fatal 
# # 允许警告（避免非致命警告终止编译）

# # ====================== capstone路径 ======================
# # 方式1：绝对路径（推荐，避免目录切换导致路径错误）
# LIBCAPSTONE = /home/shuyv/ysyx-workbench/nemu/tools/capstone/repo/libcapstone.so.5
# CAPSTONE_INC = -I /home/shuyv/ysyx-workbench/nemu/tools/capstone/repo/include
# # 链接时指定capstone库的绝对路径（或用-L指定库目录+ -lcapstone）
# CAPSTONE_LD = -L /home/shuyv/ysyx-workbench/nemu/tools/capstone/repo -lcapstone

# # 方式2：相对路径（npc2和nemu同级，用../nemu/指向nemu目录）
# # LIBCAPSTONE = ../nemu/tools/capstone/repo/libcapstone.so.5
# # CAPSTONE_INC = -I ../nemu/tools/capstone/repo/include
# # CAPSTONE_LD = -L ../nemu/tools/capstone/repo -lcapstone


# VERILATOR_FLAGS += -CFLAGS "$(CAPSTONE_INC)" -LDFLAGS "$(CAPSTONE_LD)"

# # =====================================================================

# # 文件路径配置
# VERILOG_SRC = vsrc/*.v      # Verilog源文件路径
# CPP_SRC = csrc_sdb/*.cpp        # C++测试文件路径
# C_SRC = csrc_sdb/*.c

# #VERILOG_SRC = can_runmini_bag_main/test_all/vsrc_mem/*.v      # Verilog源文件路径
# #CPP_SRC = test_all/csrc/*.cpp        # C++测试文件路径
# #C_SRC = can_runmini_bag_main/test_all/csrc/*.c

# #或排除多个文件（用 | 分隔关键词）
# # C_SRC = $(shell ls csrc/*.c | grep -v -E "skip_1.c|skip_2.c")
# EXE = obj_dir/Vtop             # Verilator生成的可执行文件（因文件名为top.v，生成Vtop）
# WAVE_FILE = sim/wave_top.vcd    # 波形文件路径
# WAVE_FILE_LAYOUT = wave_layout/wave_config.gtkw #展开初始化


# # 构建目标
# all: run wave


# # ====================== capstone库的构建规则 ======================
# # 构建capstone库：进入nemu下的capstone目录编译
# $(LIBCAPSTONE):
# 	$(MAKE) -C /home/shuyv/ysyx-workbench/nemu/tools/capstone
# 	# 若用相对路径则改为：$(MAKE) -C ../nemu/tools/capstone
# # ==================================================================

# # 编译并运行仿真
# run: $(LIBCAPSTONE)
# 	mkdir -p sim                  # 创建仿真输出目录
# 	$(VERILATOR) $(VERILATOR_FLAGS) $(VERILOG_SRC) $(CPP_SRC) $(C_SRC) # 编译
# 	./$(EXE)                      # 运行仿真
# #run:
# #	mkdir -p sim                  # 创建仿真输出目录
# #	$(VERILATOR) $(VERILATOR_FLAGS) $(VERILOG_SRC) $(CPP_SRC) $(C_SRC) # 编译
# #	./$(EXE)                      # 运行仿真


# # 查看波形
# wave:
# 	@if [ -f $(WAVE_FILE) ]; then \
# 		gtkwave $(WAVE_FILE) $(WAVE_FILE_LAYOUT); \
# 	else \
# 		echo "Error: 波形文件 $(WAVE_FILE) 不存在，请先运行仿真"; \
# 	fi

# # 清理编译产物
# clean:
# 	rm -rf obj_dir sim ./*.vcd
# 	rm -f $(EXE)
# # 可选：清理nemu下的capstone编译产物
# # $(MAKE) -C /home/shuyv/ysyx-workbench/nemu/tools/capstone clean
# # 相对路径版：$(MAKE) -C ../nemu/tools/capstone clean

# # 伪目标声明
# .PHONY: all run wave clean