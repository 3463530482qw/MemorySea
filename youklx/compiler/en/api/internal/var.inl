std::ifstream file;
std::string line;
int linen = 0;
std::vector<std::string> token;
std::unordered_map<std::string, std::any> global;
bool errored = false;
Lexing lex;