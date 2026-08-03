// 词法分析 —— 移植自 rswier/c4 (GPL v2) 的 next()
// 字符 token 直接用 ASCII 值,标识符用滚动哈希查符号表

namespace {
    // 指令名表(每条固定 4 字符,配合 %8.4s 打印对齐)
    const char* const opnames[] = {
        "LEA ", "IMM ", "JMP ", "JSR ", "BZ  ", "BNZ ", "ENT ", "ADJ ", "LEV ", "LI  ", "LC  ", "SI  ", "SC  ", "PSH ",
        "OR  ", "XOR ", "AND ", "EQ  ", "NE  ", "LT  ", "GT  ", "LE  ", "GE  ", "SHL ", "SHR ", "ADD ", "SUB ", "MUL ", "DIV ", "MOD ",
        "OPEN", "READ", "CLOS", "PRTF", "MALC", "FREE", "MSET", "MCMP", "EXIT"
    };
}

namespace youklx {
    void Compiler::next() {
        const char* pp;

        while ((tk = *p)) {
            ++p;
            if (tk == '\n') {
                // -s 模式:打印源码行和已发射的汇编
                if (src) {
                    printf("%lld: %.*s", (long long)line, (int)(p - lp), lp);
                    lp = p;
                    while (le < e) {
                        printf("%8.4s", opnames[*++le]);
                        if (*le <= ADJ) printf(" %lld\n", (long long)*++le); else printf("\n");
                    }
                }
                ++line;
            }
            else if (tk == '#') {
                // 跳过预处理指令整行
                while (*p != 0 && *p != '\n') ++p;
            }
            else if ((tk >= 'a' && tk <= 'z') || (tk >= 'A' && tk <= 'Z') || tk == '_') {
                // 标识符:滚动哈希,再线性查符号表
                pp = p - 1;
                while ((*p >= 'a' && *p <= 'z') || (*p >= 'A' && *p <= 'Z') || (*p >= '0' && *p <= '9') || *p == '_')
                    tk = tk * 147 + *p++;
                tk = (tk << 6) + (p - pp);
                id = sym;
                while (id[Tk]) {
                    if (tk == id[Hash] && !memcmp((char*)id[Name], pp, p - pp)) { tk = id[Tk]; return; }
                    id = id + Idsz;
                }
                id[Name] = (int64_t)(uintptr_t)pp;
                id[Hash] = tk;
                tk = id[Tk] = Id;
                return;
            }
            else if (tk >= '0' && tk <= '9') {
                // 数字:十进制 / 十六进制 / 八进制
                if ((ival = tk - '0')) { while (*p >= '0' && *p <= '9') ival = ival * 10 + *p++ - '0'; }
                else if (*p == 'x' || *p == 'X') {
                    while ((tk = *++p) && ((tk >= '0' && tk <= '9') || (tk >= 'a' && tk <= 'f') || (tk >= 'A' && tk <= 'F')))
                        ival = ival * 16 + (tk & 15) + (tk >= 'A' ? 9 : 0);
                }
                else { while (*p >= '0' && *p <= '7') ival = ival * 8 + *p++ - '0'; }
                tk = Num;
                return;
            }
            else if (tk == '/') {
                if (*p == '/') {
                    // 行注释
                    ++p;
                    while (*p != 0 && *p != '\n') ++p;
                }
                else {
                    tk = Div;
                    return;
                }
            }
            else if (tk == '\'' || tk == '"') {
                // 字符常量或字符串字面量(字符串直接写进数据段)
                pp = data;
                while (*p != 0 && *p != tk) {
                    if ((ival = *p++) == '\\') {
                        if ((ival = *p++) == 'n') ival = '\n';
                    }
                    if (tk == '"') *data++ = (char)ival;
                }
                ++p;
                if (tk == '"') ival = (int64_t)(uintptr_t)pp; else tk = Num;
                return;
            }
            else if (tk == '=') { if (*p == '=') { ++p; tk = Eq; } else tk = Assign; return; }
            else if (tk == '+') { if (*p == '+') { ++p; tk = Inc; } else tk = Add; return; }
            else if (tk == '-') { if (*p == '-') { ++p; tk = Dec; } else tk = Sub; return; }
            else if (tk == '!') { if (*p == '=') { ++p; tk = Ne; } return; }
            else if (tk == '<') { if (*p == '=') { ++p; tk = Le; } else if (*p == '<') { ++p; tk = Shl; } else tk = Lt; return; }
            else if (tk == '>') { if (*p == '=') { ++p; tk = Ge; } else if (*p == '>') { ++p; tk = Shr; } else tk = Gt; return; }
            else if (tk == '|') { if (*p == '|') { ++p; tk = Lor; } else tk = Or; return; }
            else if (tk == '&') { if (*p == '&') { ++p; tk = Lan; } else tk = And; return; }
            else if (tk == '^') { tk = Xor; return; }
            else if (tk == '%') { tk = Mod; return; }
            else if (tk == '*') { tk = Mul; return; }
            else if (tk == '[') { tk = Brak; return; }
            else if (tk == '?') { tk = Cond; return; }
            else if (tk == '~' || tk == ';' || tk == '{' || tk == '}' || tk == '(' || tk == ')' || tk == ']' || tk == ',' || tk == ':') return;
        }
    }
}
