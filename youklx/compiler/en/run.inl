// 虚拟机执行 —— 移植自 rswier/c4 (GPL v2) 的 main() 后半部分
// 栈池从高位地址向下生长;OPEN/READ/CLOS 用 C 标准 fopen/fread/fclose 代替 POSIX 调用

namespace youklx {
    void Compiler::run() {
        int64_t *pc, *sp, *bp, a, cycle; // 虚拟机寄存器
        int64_t i, *t; // 临时变量

        pc = (int64_t*)idmain[Val]; // main 入口
        if (src) return; // -s 模式不执行

        // 初始化栈:把 argc/argv 传给被编译程序的 main,main 返回时执行 EXIT
        bp = sp = stack_pool.data() + poolsz;
        *--sp = EXIT; // main 返回则调用 exit
        *--sp = PSH; t = sp;
        *--sp = argc;
        *--sp = (int64_t)(uintptr_t)argv;
        *--sp = (int64_t)t;

        // 执行循环
        cycle = 0;
        while (1) {
            i = *pc++; ++cycle;
            if (debug) {
                // -d 模式:打印每条指令
                printf("%lld> %.4s", (long long)cycle, opnames[i]);
                if (i <= ADJ) printf(" %lld\n", (long long)*pc); else printf("\n");
            }
            if      (i == LEA) a = (int64_t)(bp + *pc++);                             // 取局部变量地址
            else if (i == IMM) a = *pc++;                                             // 取立即数或全局地址
            else if (i == JMP) pc = (int64_t*)*pc;                                    // 跳转
            else if (i == JSR) { *--sp = (int64_t)(pc + 1); pc = (int64_t*)*pc; }     // 调用子程序
            else if (i == BZ)  pc = a ? pc + 1 : (int64_t*)*pc;                       // 为零则跳转
            else if (i == BNZ) pc = a ? (int64_t*)*pc : pc + 1;                       // 非零则跳转
            else if (i == ENT) { *--sp = (int64_t)bp; bp = sp; sp = sp - *pc++; }     // 进入子程序
            else if (i == ADJ) sp = sp + *pc++;                                       // 栈调整
            else if (i == LEV) { sp = bp; bp = (int64_t*)*sp++; pc = (int64_t*)*sp++; } // 离开子程序
            else if (i == LI)  a = *(int64_t*)a;                                      // 读整数
            else if (i == LC)  a = *(char*)a;                                         // 读字符
            else if (i == SI)  *(int64_t*)*sp++ = a;                                  // 写整数
            else if (i == SC)  a = *(char*)*sp++ = a;                                 // 写字符
            else if (i == PSH) *--sp = a;                                             // 压栈

            else if (i == OR)  a = *sp++ |  a;
            else if (i == XOR) a = *sp++ ^  a;
            else if (i == AND) a = *sp++ &  a;
            else if (i == EQ)  a = *sp++ == a;
            else if (i == NE)  a = *sp++ != a;
            else if (i == LT)  a = *sp++ <  a;
            else if (i == GT)  a = *sp++ >  a;
            else if (i == LE)  a = *sp++ <= a;
            else if (i == GE)  a = *sp++ >= a;
            else if (i == SHL) a = *sp++ << a;
            else if (i == SHR) a = *sp++ >> a;
            else if (i == ADD) a = *sp++ +  a;
            else if (i == SUB) a = *sp++ -  a;
            else if (i == MUL) a = *sp++ *  a;
            else if (i == DIV) a = *sp++ /  a;
            else if (i == MOD) a = *sp++ %  a;

            else if (i == OPEN) { FILE* f = fopen((char*)sp[1], "rb"); a = f ? (int64_t)(intptr_t)f : -1; } // 只读打开
            else if (i == READ) a = fread((char*)sp[1], 1, (size_t)*sp, (FILE*)(intptr_t)sp[2]);
            else if (i == CLOS) a = fclose((FILE*)(intptr_t)*sp);
            else if (i == PRTF) { t = sp + pc[1]; a = printf((char*)t[-1], t[-2], t[-3], t[-4], t[-5], t[-6]); }
            else if (i == MALC) a = (int64_t)(intptr_t)malloc((size_t)*sp);
            else if (i == FREE) free((void*)(intptr_t)*sp);
            else if (i == MSET) a = (int64_t)(intptr_t)memset((char*)sp[2], (int)sp[1], (size_t)*sp);
            else if (i == MCMP) a = memcmp((char*)sp[2], (char*)sp[1], (size_t)*sp);
            else if (i == EXIT) { printf("exit(%lld) cycle = %lld\n", (long long)*sp, (long long)cycle); return; }
            else throw std::runtime_error("unknown instruction = " + std::to_string(i) + "! cycle = " + std::to_string(cycle));
        }
    }
}
