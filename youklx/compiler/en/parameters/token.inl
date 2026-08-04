namespace youklx {
    // 词法记号类型：目前只支持数字和加法
    enum class TokenType {
        数字,   // 数字字面量，如 1、3.14
        加号,   // +
        结束,   // 一行已扫描完毕
    };

    // 词法记号
    struct Token {
        TokenType type;
        double value = 0;   // 仅数字记号有意义
    };
}
