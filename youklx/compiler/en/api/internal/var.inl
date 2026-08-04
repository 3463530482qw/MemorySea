std::ifstream file;
std::string line;
int linen = 0;
std::vector<Token> tokens;   // 当前行的分词结果
size_t pos = 0;              // 解析器当前位置