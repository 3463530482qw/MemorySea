namespace youklx {
    // 表达式节点（AST）：数字字面量
    struct NumberNode {
        double value;
    };

    struct ExprNode;    // 前向声明，供加法节点递归引用

    // 表达式节点（AST）：加法运算，左右各一棵子表达式
    struct AddNode {
        std::unique_ptr<ExprNode> left;
        std::unique_ptr<ExprNode> right;
    };

    // 表达式树：数字 或 加法
    struct ExprNode {
        std::variant<NumberNode, AddNode> data;
    };
}
