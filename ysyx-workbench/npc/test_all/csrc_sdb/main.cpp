#include "Vtop.h"
#include "common.h"
#include "utils.h"

const uint32_t MEM_SIZE = 0x10000000;
std::vector<uint32_t> pmem(MEM_SIZE, 0);
std::vector<uint32_t> pmem_rom(MEM_SIZE, 0);

int main(int argc, char** argv) {
    // 加载程序
    std::string bin_path = (argc > 1) ? argv[1]
       : "/home/shuyv/ysyx-workbench/am-kernels/tests/cpu-tests/build/bit-minirv-npc.bin";
        //: "/home/shuyv/ysyx-workbench/npc/some_hex/my_hex_copy.hex";
    load_program(bin_path);

    Vtop* top = nullptr;
    #ifdef ENABLE_WAVE
    VerilatedVcdC* tfp = nullptr;
    #endif

    vluint64_t main_time = 0;
    init_verilator(top, argc,argv
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
    #define MAX_CYCLES 100000000
    

    //npc状态机
    #define NPC_RUNNING 1
    #define NPC_END 0
    int npc_state = NPC_RUNNING;

    bool running = false;
    uint64_t cycle = 0;
    while (1){
        if (running) {
            // 连续运行模式：每个周期检查一次 ebreak
            top->clk = 0; top->eval();
#ifdef ENABLE_WAVE
            tfp->dump(main_time);
#endif
            main_time += 10;

            if (top->is_ebreak) {
                if (npc_state == NPC_END)
                {
                  printf("Program execution has ended. To restart the program, exit NPC and run again.\n");
                  running = false;
                }
                else
                {
                  npc_state = NPC_END;
                  printf("Hit ebreak at cycle %lu, PC = 0x%08x\n", cycle, top->pc);
                  if (top->a0 == 0) {
                    printf("PASS! (a0 == 0)\n");
                  } else {
                    printf("FAIL! (a0 = 0x%08x)\n", top->a0);
                  }
                  running = false;
                }
            }

            if (cycle >= MAX_CYCLES) {
                printf("达到最大周期限制 %u，强制停止\n", MAX_CYCLES);
                running = false;
            }

            if (!running) {
                // 停下来进入命令模式
                printf("(npc) ");
                fflush(stdout);
            } else {
                top->clk = 1; top->eval();
                #ifdef ENABLE_WAVE
                tfp->dump(main_time);
                #endif
                main_time += 10;
                cycle++;
                continue;
            }
        }

        // 命令模式
        //提取指令
        char cmd[128];
        if (!fgets(cmd, sizeof(cmd), stdin)) break;
        cmd[strcspn(cmd, "\n")] = 0;  // 去掉换行

        if (strlen(cmd) == 0) {
           printf("(npc) ");
           fflush(stdout);
           continue;
        }


        //q指令
        if (strcmp(cmd, "q") == 0 || strcmp(cmd, "quit") == 0) {
            break;
        }

        //c指令
        else if (strcmp(cmd, "c") == 0 || strcmp(cmd, "continue") == 0) {
            running = true;
            continue;
        }

        //si指令
        else if (strncmp(cmd, "si", 2) == 0) {
            int steps = 1;
            sscanf(cmd + 2, "%d", &steps);
            if (steps <= 0) steps = 1;
            for (int i = 0; i < steps; i++) {
                top->clk = 0; top->eval();
#               ifdef ENABLE_WAVE
                tfp->dump(main_time);
                #endif
                main_time += 10;
                //单步执行打印指令，反汇编未添加
                uint32_t current_pc = top->pc;
                uint32_t current_inst = pmem_read(current_pc);  // 推荐用这个，避免依赖 inst 端口
                printf("0x%08x: %08x\n", current_pc, current_inst);
                if (top->is_ebreak) {
                    printf("Hit ebreak during si at cycle %lu\n", cycle);
                    break;
                }

                top->clk = 1; top->eval();
#ifdef ENABLE_WAVE
                tfp->dump(main_time);
#endif
                main_time += 10;
                cycle++;
            }
        }

        //info r指令，未实现
        else if (strcmp(cmd, "info r") == 0 || strcmp(cmd, "r") == 0) {
            printf("还未实现 info r 指令\n");
        }


        //x指令
        else if (strncmp(cmd, "x", 1) == 0) {
            int n = 10;
            uint32_t addr = 0x80000000;

            // 简单解析：x /10 0x80001000
            sscanf(cmd + 1, "/%d %x", &n, &addr);
            if (n <= 0) n = 10;

            printf("0x%08x:", addr);
            for (int i = 0; i < n; i++) {
                uint32_t word = pmem_read(addr + i*4);
                printf("  %08x", word);
                if ((i+1) % 4 == 0) printf("\n          ");
            }
            printf("\n");
        }
        else {
            printf("未知命令: %s\n支持: c, si [N], info r, x /N addr, q\n", cmd);
        }

        printf("(npc) ");
        fflush(stdout);
    }
    print_simulation_result(top, cycle);  // 假设每个周期 20ps

#ifdef ENABLE_WAVE
    tfp->dump(main_time);
    tfp->close();
    delete tfp;
#endif

    delete top;
    return 0;
}