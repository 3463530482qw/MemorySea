//#include "parameters/dll.cpp"
namespace youklx {
    class Sence{
        public:
            std::unordered_map<std::string, std::function<void ()>> dict{};
            std::set<HMODULE> handles{};
            std::string ptr;
        public:
            ~Sence();
            Sence& ldll(std::string dll, std::string nfun);
    };
}

#include "ldll.cpp"