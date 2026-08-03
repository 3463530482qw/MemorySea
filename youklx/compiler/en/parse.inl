// 语法分析 —— 移植自 rswier/c4 (GPL v2) 的 expr()/stmt()/声明解析
// 优先级爬升法处理全部运算符;错误统一抛 std::runtime_error(原版为 exit)

namespace youklx {
    // 表达式解析:lev 是当前允许的最低运算符优先级
    void Compiler::expr(int64_t lev) {
        int64_t t, *d;

        if (!tk) throw std::runtime_error(std::to_string(line) + ": unexpected eof in expression");
        else if (tk == Num) { *++e = IMM; *++e = ival; next(); ty = INT; }
        else if (tk == '"') {
            // 字符串字面量:地址即 ival,后续按数据段 8 字节对齐
            *++e = IMM; *++e = ival; next();
            while (tk == '"') next();
            data = (char*)(((int64_t)data + sizeof(int64_t)) & -(int64_t)sizeof(int64_t)); ty = PTR;
        }
        else if (tk == Sizeof) {
            next(); if (tk == '(') next(); else throw std::runtime_error(std::to_string(line) + ": open paren expected in sizeof");
            ty = INT; if (tk == Int) next(); else if (tk == Char) { next(); ty = CHAR; }
            while (tk == Mul) { next(); ty = ty + PTR; }
            if (tk == ')') next(); else throw std::runtime_error(std::to_string(line) + ": close paren expected in sizeof");
            *++e = IMM; *++e = (ty == CHAR) ? sizeof(char) : sizeof(int64_t);
            ty = INT;
        }
        else if (tk == Id) {
            d = id; next();
            if (tk == '(') {
                // 函数调用
                next();
                t = 0;
                while (tk != ')') { expr(Assign); *++e = PSH; ++t; if (tk == ',') next(); }
                next();
                if (d[Class] == Sys) *++e = d[Val]; // 库函数:直接发指令码
                else if (d[Class] == Fun) { *++e = JSR; *++e = d[Val]; }
                else throw std::runtime_error(std::to_string(line) + ": bad function call");
                if (t) { *++e = ADJ; *++e = t; }
                ty = d[Type];
            }
            else if (d[Class] == Num) { *++e = IMM; *++e = d[Val]; ty = INT; }
            else {
                // 变量:局部取地址、全局取地址、按类型取字符或整数
                if (d[Class] == Loc) { *++e = LEA; *++e = loc - d[Val]; }
                else if (d[Class] == Glo) { *++e = IMM; *++e = d[Val]; }
                else throw std::runtime_error(std::to_string(line) + ": undefined variable");
                *++e = ((ty = d[Type]) == CHAR) ? LC : LI;
            }
        }
        else if (tk == '(') {
            next();
            if (tk == Int || tk == Char) {
                // 类型强转
                t = (tk == Int) ? INT : CHAR; next();
                while (tk == Mul) { next(); t = t + PTR; }
                if (tk == ')') next(); else throw std::runtime_error(std::to_string(line) + ": bad cast");
                expr(Inc);
                ty = t;
            }
            else {
                expr(Assign);
                if (tk == ')') next(); else throw std::runtime_error(std::to_string(line) + ": close paren expected");
            }
        }
        else if (tk == Mul) {
            // 解引用
            next(); expr(Inc);
            if (ty > INT) ty = ty - PTR; else throw std::runtime_error(std::to_string(line) + ": bad dereference");
            *++e = (ty == CHAR) ? LC : LI;
        }
        else if (tk == And) {
            // 取地址:吞掉前面的取址指令
            next(); expr(Inc);
            if (*e == LC || *e == LI) --e; else throw std::runtime_error(std::to_string(line) + ": bad address-of");
            ty = ty + PTR;
        }
        else if (tk == '!') { next(); expr(Inc); *++e = PSH; *++e = IMM; *++e = 0; *++e = EQ; ty = INT; }
        else if (tk == '~') { next(); expr(Inc); *++e = PSH; *++e = IMM; *++e = -1; *++e = XOR; ty = INT; }
        else if (tk == Add) { next(); expr(Inc); ty = INT; }
        else if (tk == Sub) {
            next(); *++e = IMM;
            if (tk == Num) { *++e = -ival; next(); } else { *++e = -1; *++e = PSH; expr(Inc); *++e = MUL; }
            ty = INT;
        }
        else if (tk == Inc || tk == Dec) {
            // 前缀自增/自减
            t = tk; next(); expr(Inc);
            if (*e == LC) { *e = PSH; *++e = LC; }
            else if (*e == LI) { *e = PSH; *++e = LI; }
            else throw std::runtime_error(std::to_string(line) + ": bad lvalue in pre-increment");
            *++e = PSH;
            *++e = IMM; *++e = (ty > PTR) ? sizeof(int64_t) : sizeof(char);
            *++e = (t == Inc) ? ADD : SUB;
            *++e = (ty == CHAR) ? SC : SI;
        }
        else throw std::runtime_error(std::to_string(line) + ": bad expression");

        // 优先级爬升:处理二元运算符、赋值、三目、下标、后缀自增自减
        while (tk >= lev) {
            t = ty;
            if (tk == Assign) {
                next();
                if (*e == LC || *e == LI) *e = PSH; else throw std::runtime_error(std::to_string(line) + ": bad lvalue in assignment");
                expr(Assign); *++e = ((ty = t) == CHAR) ? SC : SI;
            }
            else if (tk == Cond) {
                next();
                *++e = BZ; d = ++e;
                expr(Assign);
                if (tk == ':') next(); else throw std::runtime_error(std::to_string(line) + ": conditional missing colon");
                *d = (int64_t)(e + 3); *++e = JMP; d = ++e;
                expr(Cond);
                *d = (int64_t)(e + 1);
            }
            else if (tk == Lor) { next(); *++e = BNZ; d = ++e; expr(Lan); *d = (int64_t)(e + 1); ty = INT; }
            else if (tk == Lan) { next(); *++e = BZ;  d = ++e; expr(Or);  *d = (int64_t)(e + 1); ty = INT; }
            else if (tk == Or)  { next(); *++e = PSH; expr(Xor); *++e = OR;  ty = INT; }
            else if (tk == Xor) { next(); *++e = PSH; expr(And); *++e = XOR; ty = INT; }
            else if (tk == And) { next(); *++e = PSH; expr(Eq);  *++e = AND; ty = INT; }
            else if (tk == Eq)  { next(); *++e = PSH; expr(Lt);  *++e = EQ;  ty = INT; }
            else if (tk == Ne)  { next(); *++e = PSH; expr(Lt);  *++e = NE;  ty = INT; }
            else if (tk == Lt)  { next(); *++e = PSH; expr(Shl); *++e = LT;  ty = INT; }
            else if (tk == Gt)  { next(); *++e = PSH; expr(Shl); *++e = GT;  ty = INT; }
            else if (tk == Le)  { next(); *++e = PSH; expr(Shl); *++e = LE;  ty = INT; }
            else if (tk == Ge)  { next(); *++e = PSH; expr(Shl); *++e = GE;  ty = INT; }
            else if (tk == Shl) { next(); *++e = PSH; expr(Add); *++e = SHL; ty = INT; }
            else if (tk == Shr) { next(); *++e = PSH; expr(Add); *++e = SHR; ty = INT; }
            else if (tk == Add) {
                next(); *++e = PSH; expr(Mul);
                if ((ty = t) > PTR) { *++e = PSH; *++e = IMM; *++e = sizeof(int64_t); *++e = MUL;  } // 指针加整数要乘单元大小
                *++e = ADD;
            }
            else if (tk == Sub) {
                next(); *++e = PSH; expr(Mul);
                if (t > PTR && t == ty) { *++e = SUB; *++e = PSH; *++e = IMM; *++e = sizeof(int64_t); *++e = DIV; ty = INT; } // 指针减指针
                else if ((ty = t) > PTR) { *++e = PSH; *++e = IMM; *++e = sizeof(int64_t); *++e = MUL; *++e = SUB; }
                else *++e = SUB;
            }
            else if (tk == Mul) { next(); *++e = PSH; expr(Inc); *++e = MUL; ty = INT; }
            else if (tk == Div) { next(); *++e = PSH; expr(Inc); *++e = DIV; ty = INT; }
            else if (tk == Mod) { next(); *++e = PSH; expr(Inc); *++e = MOD; ty = INT; }
            else if (tk == Inc || tk == Dec) {
                // 后缀自增/自减:先取旧值,再加/减写回
                if (*e == LC) { *e = PSH; *++e = LC; }
                else if (*e == LI) { *e = PSH; *++e = LI; }
                else throw std::runtime_error(std::to_string(line) + ": bad lvalue in post-increment");
                *++e = PSH; *++e = IMM; *++e = (ty > PTR) ? sizeof(int64_t) : sizeof(char);
                *++e = (tk == Inc) ? ADD : SUB;
                *++e = (ty == CHAR) ? SC : SI;
                *++e = PSH; *++e = IMM; *++e = (ty > PTR) ? sizeof(int64_t) : sizeof(char);
                *++e = (tk == Inc) ? SUB : ADD;
                next();
            }
            else if (tk == Brak) {
                // 下标:指针 + 索引*单元大小
                next(); *++e = PSH; expr(Assign);
                if (tk == ']') next(); else throw std::runtime_error(std::to_string(line) + ": close bracket expected");
                if (t > PTR) { *++e = PSH; *++e = IMM; *++e = sizeof(int64_t); *++e = MUL;  }
                else if (t < PTR) throw std::runtime_error(std::to_string(line) + ": pointer type expected");
                *++e = ADD;
                *++e = ((ty = t - PTR) == CHAR) ? LC : LI;
            }
            else throw std::runtime_error(std::to_string(line) + ": compiler error tk=" + std::to_string(tk));
        }
    }

    // 语句解析
    void Compiler::stmt() {
        int64_t *a, *b;

        if (tk == If) {
            next();
            if (tk == '(') next(); else throw std::runtime_error(std::to_string(line) + ": open paren expected");
            expr(Assign);
            if (tk == ')') next(); else throw std::runtime_error(std::to_string(line) + ": close paren expected");
            *++e = BZ; b = ++e;
            stmt();
            if (tk == Else) {
                *b = (int64_t)(e + 3); *++e = JMP; b = ++e;
                next();
                stmt();
            }
            *b = (int64_t)(e + 1);
        }
        else if (tk == While) {
            next();
            a = e + 1;
            if (tk == '(') next(); else throw std::runtime_error(std::to_string(line) + ": open paren expected");
            expr(Assign);
            if (tk == ')') next(); else throw std::runtime_error(std::to_string(line) + ": close paren expected");
            *++e = BZ; b = ++e;
            stmt();
            *++e = JMP; *++e = (int64_t)a;
            *b = (int64_t)(e + 1);
        }
        else if (tk == Return) {
            next();
            if (tk != ';') expr(Assign);
            *++e = LEV;
            if (tk == ';') next(); else throw std::runtime_error(std::to_string(line) + ": semicolon expected");
        }
        else if (tk == '{') {
            next();
            while (tk != '}') stmt();
            next();
        }
        else if (tk == ';') {
            next();
        }
        else {
            expr(Assign);
            if (tk == ';') next(); else throw std::runtime_error(std::to_string(line) + ": semicolon expected");
        }
    }

    // 全局声明解析 + 编译(原版 main 的解析部分)
    void Compiler::parse() {
        int64_t i, bt, ty;

        // 关键字和库函数进符号表
        p = "char else enum if int return sizeof while "
            "open read close printf malloc free memset memcmp exit void main";
        i = Char; while (i <= While) { next(); id[Tk] = i++; } // 关键字
        i = OPEN; while (i <= EXIT) { next(); id[Class] = Sys; id[Type] = INT; id[Val] = i++; } // 库函数
        next(); id[Tk] = Char; // 处理 void 类型
        next(); idmain = id; // 记住 main 的符号表项

        // 开始解析源码
        line = 1;
        p = lp = src_buf.data();
        next();
        while (tk) {
            bt = INT; // 基本类型
            if (tk == Int) next();
            else if (tk == Char) { next(); bt = CHAR; }
            else if (tk == Enum) {
                // 枚举:成员按顺序编号,可显式赋值
                next();
                if (tk != '{') next();
                if (tk == '{') {
                    next();
                    i = 0;
                    while (tk != '}') {
                        if (tk != Id) throw std::runtime_error(std::to_string(line) + ": bad enum identifier " + std::to_string(tk));
                        next();
                        if (tk == Assign) {
                            next();
                            if (tk != Num) throw std::runtime_error(std::to_string(line) + ": bad enum initializer");
                            i = ival;
                            next();
                        }
                        id[Class] = Num; id[Type] = INT; id[Val] = i++;
                        if (tk == ',') next();
                    }
                    next();
                }
            }
            while (tk != ';' && tk != '}') {
                ty = bt;
                while (tk == Mul) { next(); ty = ty + PTR; }
                if (tk != Id) throw std::runtime_error(std::to_string(line) + ": bad global declaration");
                if (id[Class]) throw std::runtime_error(std::to_string(line) + ": duplicate global definition");
                next();
                id[Type] = ty;
                if (tk == '(') { // 函数定义
                    id[Class] = Fun;
                    id[Val] = (int64_t)(e + 1);
                    next(); i = 0;
                    while (tk != ')') {
                        // 参数:原符号表字段暂存到 H* 位置,以便函数结束后还原
                        ty = INT;
                        if (tk == Int) next();
                        else if (tk == Char) { next(); ty = CHAR; }
                        while (tk == Mul) { next(); ty = ty + PTR; }
                        if (tk != Id) throw std::runtime_error(std::to_string(line) + ": bad parameter declaration");
                        if (id[Class] == Loc) throw std::runtime_error(std::to_string(line) + ": duplicate parameter definition");
                        id[HClass] = id[Class]; id[Class] = Loc;
                        id[HType]  = id[Type];  id[Type] = ty;
                        id[HVal]   = id[Val];   id[Val] = i++;
                        next();
                        if (tk == ',') next();
                    }
                    next();
                    if (tk != '{') throw std::runtime_error(std::to_string(line) + ": bad function definition");
                    loc = ++i;
                    next();
                    while (tk == Int || tk == Char) {
                        // 局部变量声明
                        bt = (tk == Int) ? INT : CHAR;
                        next();
                        while (tk != ';') {
                            ty = bt;
                            while (tk == Mul) { next(); ty = ty + PTR; }
                            if (tk != Id) throw std::runtime_error(std::to_string(line) + ": bad local declaration");
                            if (id[Class] == Loc) throw std::runtime_error(std::to_string(line) + ": duplicate local definition");
                            id[HClass] = id[Class]; id[Class] = Loc;
                            id[HType]  = id[Type];  id[Type] = ty;
                            id[HVal]   = id[Val];   id[Val] = ++i;
                            next();
                            if (tk == ',') next();
                        }
                        next();
                    }
                    *++e = ENT; *++e = i - loc; // 进入函数:分配局部变量空间
                    while (tk != '}') stmt();
                    *++e = LEV;
                    id = sym; // 还原符号表中的局部项
                    while (id[Tk]) {
                        if (id[Class] == Loc) {
                            id[Class] = id[HClass];
                            id[Type] = id[HType];
                            id[Val] = id[HVal];
                        }
                        id = id + Idsz;
                    }
                }
                else {
                    // 全局变量:分配数据段空间
                    id[Class] = Glo;
                    id[Val] = (int64_t)(uintptr_t)data;
                    data = data + sizeof(int64_t);
                }
                if (tk == ',') next();
            }
            next();
        }

        if (!idmain[Val]) throw std::runtime_error("main() not defined");
        if (src) return; // -s 模式只打印,不执行
    }
}
