#***************************************************************************************
# Copyright (c) 2014-2024 Zihao Yu, Nanjing University
#
# NEMU is licensed under Mulan PSL v2.
# You can use this software according to the terms and conditions of the Mulan PSL v2.
# You may obtain a copy of Mulan PSL v2 at:
#          http://license.coscl.org.cn/MulanPSL2
#
# THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
# EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
# MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
#
# See the Mulan PSL v2 for more details.
#**************************************************************************************/

# 核心优化1：启用make的严格模式，减少依赖解析歧义
SHELL := /bin/bash
.SUFFIXES:
MAKEFLAGS += --no-builtin-rules --no-builtin-variables

REPO_PATH = repo
ifeq ($(wildcard $(REPO_PATH)/spike_main),)
  $(shell git clone --depth=1 git@github.com:NJU-ProjectN/riscv-isa-sim $(REPO_PATH))
endif

REPO_BUILD_PATH = $(REPO_PATH)/build
REPO_MAKEFILE = $(REPO_BUILD_PATH)/Makefile

# 核心优化2：显式声明repo配置的依赖，避免重复执行
$(REPO_MAKEFILE):
	@mkdir -p $(@D)
	@cd $(@D) && [ -f config.status ] || $(abspath $(REPO_PATH))/configure
	@sed -i -e 's/-g -O2/-O2/' $@ >/dev/null 2>&1

# 核心优化3：显式声明静态库的依赖目标（关键：消除循环依赖误判）
LIB_RISCV = $(REPO_BUILD_PATH)/libriscv.a
LIB_SOFTFLOAT = $(REPO_BUILD_PATH)/libsoftfloat.a
LIB_DISASM = $(REPO_BUILD_PATH)/libdisasm.a
LIB_FESVR = $(REPO_BUILD_PATH)/libfesvr.a
LIB_FDT = $(REPO_BUILD_PATH)/libfdt.a
LIB_SPIKE_MAIN = $(REPO_BUILD_PATH)/libspike_main.a

# 静态库依赖spike的编译结果，确保先编译静态库再链接
$(LIB_RISCV) $(LIB_SOFTFLOAT) $(LIB_DISASM) $(LIB_FESVR) $(LIB_FDT) $(LIB_SPIKE_MAIN): $(SPIKE)

SPIKE = $(REPO_BUILD_PATH)/spike
$(SPIKE): $(REPO_MAKEFILE)
	@echo "Building spike..."
	CFLAGS="-fvisibility=hidden" CXXFLAGS="-fvisibility=hidden" $(MAKE) -C $(^D) -j$(nproc) >/dev/null 2>&1

BUILD_DIR = ./build
$(shell mkdir -p $(BUILD_DIR))

inc_dependencies = fesvr riscv disasm customext fdt softfloat spike_main spike_dasm build
INC_PATH  = -I$(REPO_PATH) $(addprefix -I$(REPO_PATH)/, $(inc_dependencies))
INC_PATH += -I$(NEMU_HOME)/include
# 整合静态库列表，确保链接顺序正确（依赖在前，被依赖在后）
INC_LIBS  = $(LIB_SPIKE_MAIN) $(LIB_RISCV) $(LIB_DISASM) $(LIB_SOFTFLOAT) $(LIB_FESVR) $(LIB_FDT)

NAME = $(GUEST_ISA)-spike-so
BINARY = $(BUILD_DIR)/$(NAME)
SRCS = difftest.cc

# 核心优化4：$(BINARY)显式依赖所有静态库，让make明确依赖顺序
$(BINARY): $(SRCS) $(LIB_RISCV) $(LIB_SOFTFLOAT) $(LIB_DISASM) $(LIB_FESVR) $(LIB_FDT) $(LIB_SPIKE_MAIN)
	@echo "Building spike shared library: $(NAME)..."
	g++ -std=c++17 -O2 -shared -fPIC -fvisibility=hidden \
		$(INC_PATH) $(SRCS) $(INC_LIBS) -o $@ \
		-Wl,--no-as-needed -ldl -lpthread >/dev/null 2>&1

clean:
	rm -rf $(BUILD_DIR)
	# 可选：清理repo的编译产物（如需彻底重建）
	# $(MAKE) -C $(REPO_BUILD_PATH) clean >/dev/null 2>&1

all: $(BINARY)
.DEFAULT_GOAL = all

.PHONY: all clean
# 核心优化5：移除$(SPIKE)的PHONY声明，避免make认为其是伪目标导致重复编译

#这个makefile改过了，改之前会报这个提示
#make -s -C /home/shuyv/ysyx-workbench/nemu/tools/spike-diff GUEST_ISA=riscv32 SHARE=1 ENGINE=interpreter
#make[2]: 放弃循环依赖 libriscv.so <- libriscv.so 。
#make[2]: 放弃循环依赖 libcustomext.so <- libcustomext.so 。
#make[2]: 放弃循环依赖 libsoftfloat.so <- libsoftfloat.so 。