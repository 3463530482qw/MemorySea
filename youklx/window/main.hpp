#include "parameters/create.cpp"
namespace youklx {
    class Window {
        public:
            RGFW_window* id;
        public:
            void create(windowcreateinfo& creatinfo);
        private:
    };
}

#include "create.cpp"