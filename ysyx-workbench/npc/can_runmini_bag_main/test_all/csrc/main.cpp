#include "Vtop.h"
#include "common.h"
#include "utils.h"

// #define ENABLE_WAVE

const uint32_t MEM_SIZE = 0x10000000;
std::vector<uint32_t> pmem(MEM_SIZE, 0);
std::vector<uint32_t> pmem_rom(MEM_SIZE, 0);

int main(int argc, char** argv) {
    // 加载程序
    std::string bin_path = (argc > 1) ? argv[1]
         : "/home/shuyv/ysyx-workbench/npc/some_hex/my_hex_copy.hex";
        // : "/home/shuyv/ysyx-workbench/am-kernels/tests/cpu-tests/build/bit-minirv-npc.bin";
    load_program(bin_path);

    Vtop* top = nullptr;
#ifdef ENABLE_WAVE
    VerilatedVcdC* tfp = nullptr;
#endif

    vluint64_t main_time = 0;

    
    init_verilator(
        top, argc,argv
        #ifdef ENABLE_WAVE
        ,tfp 
        #endif
        
    );
    // 复位
    reset_cpu(top, main_time
        #ifdef ENABLE_WAVE
        ,tfp
        #endif
    );



    // 运行仿真
    run_simulation(top
        #ifdef ENABLE_WAVE
        , tfp
        #endif
        , main_time
    );

    // 输出结果
    print_simulation_result(top, main_time / 20);  // 假设每个周期 20ps

#ifdef ENABLE_WAVE
    tfp->dump(main_time);
    tfp->close();
    delete tfp;
#endif

    delete top;
    return 0;
}