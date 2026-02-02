


VERILATOR = verilator
# 关键选项：指定顶层模块为am，允许警告不终止，开启多线程编译
VERILATOR_FLAGS = -Wall -j 0 --cc --exe --trace --build \
--top-module top \
--Mdir obj_dir \
-Wno-fatal 
# 允许警告（避免非致命警告终止编译）

# 文件路径配置
VERILOG_SRC = vsrc/*.v      # Verilog源文件路径
CPP_SRC = csrc_sdb/*.cpp        # C++测试文件路径
C_SRC = csrc_sdb/*.c

#VERILOG_SRC = can_runmini_bag_main/test_all/vsrc_mem/*.v      # Verilog源文件路径
#CPP_SRC = test_all/csrc/*.cpp        # C++测试文件路径
#C_SRC = can_runmini_bag_main/test_all/csrc/*.c

#或排除多个文件（用 | 分隔关键词）
# C_SRC = $(shell ls csrc/*.c | grep -v -E "skip_1.c|skip_2.c")
EXE = obj_dir/Vtop             # Verilator生成的可执行文件（因文件名为top.v，生成Vtop）
WAVE_FILE = sim/wave.vcd    # 波形文件路径
WAVE_FILE_LAYOUT = wave_layout/wave_config.gtkw #展开初始化


# 构建目标
all: run wave

# 编译并运行仿真
run:
	mkdir -p sim                  # 创建仿真输出目录
	$(VERILATOR) $(VERILATOR_FLAGS) $(VERILOG_SRC) $(CPP_SRC) $(C_SRC) # 编译
	./$(EXE)                      # 运行仿真

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

# 伪目标声明
.PHONY: all run wave clean