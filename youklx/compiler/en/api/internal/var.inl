            // —— 移植自 rswier/c4 (GPL v2) —— 微型 C 编译器内部状态
            // token 和类(运算符在后,按优先级顺序;字符 token 直接用 ASCII 值)
            enum {
                Num = 128, Fun, Sys, Glo, Loc, Id,
                Char, Else, Enum, If, Int, Return, Sizeof, While,
                Assign, Cond, Lor, Lan, Or, Xor, And, Eq, Ne, Lt, Gt, Le, Ge, Shl, Shr, Add, Sub, Mul, Div, Mod, Inc, Dec, Brak
            };
            // 虚拟机指令码
            enum { LEA ,IMM ,JMP ,JSR ,BZ  ,BNZ ,ENT ,ADJ ,LEV ,LI  ,LC  ,SI  ,SC  ,PSH ,
                   OR  ,XOR ,AND ,EQ  ,NE  ,LT  ,GT  ,LE  ,GE  ,SHL ,SHR ,ADD ,SUB ,MUL ,DIV ,MOD ,
                   OPEN,READ,CLOS,PRTF,MALC,FREE,MSET,MCMP,EXIT };
            // 类型
            enum { CHAR, INT, PTR };
            // 符号表条目偏移(没有 ident 结构体,用数组模拟)
            enum { Tk, Hash, Name, Class, Type, Val, HClass, HType, HVal, Idsz };
        private:
            // 内存池大小(原版 256KB,原样保留)
            static constexpr int64_t poolsz = 256 * 1024;

            // —— 词法/编译状态 ——
            const char* p;  // 当前源码位置(只读,可指向字符串字面量)
            const char* lp; // 当前行起点(-s 打印用)
            char* data;   // 数据段/bss 指针(也是字符串字面量池)
            int64_t* e;   // 当前发射代码位置
            int64_t* le;  // 发射代码起点(-s 打印用)
            int64_t* id;  // 当前解析的标识符
            int64_t* sym; // 符号表(标识符简单链表)
            int64_t tk;   // 当前 token
            int64_t ival; // 当前 token 值
            int64_t ty;   // 当前表达式类型
            int64_t loc;  // 局部变量偏移
            int64_t line; // 当前行号
            int64_t* idmain; // main 的符号表项(VM 入口用)

            // —— 内存池(RAII 替代原版 malloc,一次性分配后指针算术,零扩容)——
            std::vector<int64_t> sym_pool;   // 符号表池
            std::vector<int64_t> text_pool;  // 代码池
            std::vector<char> data_pool;     // 数据段池
            std::vector<int64_t> stack_pool; // 虚拟机栈池
            std::vector<char> src_buf;       // 源码缓冲