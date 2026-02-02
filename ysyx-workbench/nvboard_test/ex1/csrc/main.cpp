#include <nvboard.h>
#include <Vex1.h>

static Vex1 dut;

void nvboard_bind_all_pins(Vex1* top);

int main() {
    // 初始化NVBoard
    nvboard_bind_all_pins(&dut);
    nvboard_init();

    // 初始值设置
    dut.X1 = 0;
    dut.X2 = 0;
    dut.X3 = 0;
    dut.X0 = 0;
    dut.y1 = 0;
    dut.y2 = 0;

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
