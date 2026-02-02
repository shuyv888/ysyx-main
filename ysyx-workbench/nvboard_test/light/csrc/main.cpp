#include <nvboard.h>
#include <Vlight.h>  // 注意这里改为你的模块头文件

static Vlight dut;  // 设计实例

void nvboard_bind_all_pins(Vlight* top);  // 自动生成的绑定函数

int main() {
    // 初始化 NVBoard
    nvboard_bind_all_pins(&dut);
    nvboard_init();

    // 复位电路
    dut.rst = 1;
    for (int i = 0; i < 10; i++) {
        dut.clk = 0; dut.eval();
        dut.clk = 1; dut.eval();
    }
    dut.rst = 0;

    // 主仿真循环
    while (1) {
        nvboard_update();     // 更新 GUI 输入输出
        
        // 产生时钟信号
        dut.clk = 0; dut.eval();  // 下降沿
        dut.clk = 1; dut.eval();  // 上升沿
    }

    nvboard_quit();
    return 0;
}
