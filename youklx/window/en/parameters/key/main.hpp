namespace youklx {
    class Keyboa {
        public:
            #include "en/api/function.inl"
            #include "中文/接口/函数.inl"
        private:
            #include "en/api/internal/var.inl"
        public:
    };
    using 按键 = Keyboa;
}
#include"en/press.inl"
#include"en/hold.inl"
#include"en/release.inl"
#include"en/update.inl"