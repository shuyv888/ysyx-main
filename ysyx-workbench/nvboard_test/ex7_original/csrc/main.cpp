#include <nvboard.h>
#include <Vex7.h>

static Vex7 dut;

void nvboard_bind_all_pins(Vex7* top);

int main() {
	// 初始化NVBoard
	nvboard_bind_all_pins(&dut);
	nvboard_init();

	// 初始值设置
	dut.rst = 1;
	dut.ps2_data= 1;
    dut.ps2_clk=1;


    for (int i = 0; i < 10; i++) {
        nvboard_update();
        dut.eval();
    }


	// 主仿真循环
    while (1) {
        // 更新GUI输入输出
        nvboard_update();

        // 评估电路
        dut.eval();
    }

	nvboard_quit();
	return 0;
}
