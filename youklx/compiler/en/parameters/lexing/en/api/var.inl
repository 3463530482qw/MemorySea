std::vector<std::string>* token;
std::string* line;
std::unordered_map<std::string, void(Compiler::*)()>* kw;
std::unordered_set<unsigned char>* ichar;
size_t rptr{0};
size_t lptr{0};
unsigned char cptr;