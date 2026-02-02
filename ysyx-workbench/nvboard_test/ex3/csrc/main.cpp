#include <nvboard.h>
#include <Vex3.h>

static Vex3 dut;

void nvboard_bind_all_pins(Vex3* top);

int main() {
    // 初始化NVBoard
    nvboard_bind_all_pins(&dut);
    nvboard_init();

    // 初始值设置
    dut.in = 0;

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
