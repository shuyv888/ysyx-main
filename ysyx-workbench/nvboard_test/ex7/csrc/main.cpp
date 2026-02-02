#include <nvboard.h>
#include <Vex7.h>

static Vex7 dut;

void nvboard_bind_all_pins(Vex7* top);


static void single_cycle() {
  dut.clk = 0; dut.eval();
  dut.clk = 1; dut.eval();
}

static void rst_init() {
  dut.rst = 1;
  dut.clk = 0; dut.eval();
  dut.clk = 1; dut.eval();
  dut.clk = 0; dut.eval();
  dut.clk = 1; 
  dut.rst = 0; dut.eval();
}


int main() {
	// 初始化NVBoard
	nvboard_bind_all_pins(&dut);
	nvboard_init();

	rst_init();


	// 主仿真循环
    while (1) {
        // 更新GUI输入输出
        nvboard_update();
		    single_cycle();
        // 评估电路

    }

	nvboard_quit();
	return 0;
}
