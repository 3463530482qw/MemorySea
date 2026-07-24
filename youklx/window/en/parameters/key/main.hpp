namespace youklx {
    class Keyboa {
        public:
            #include "en/api/function.inl"
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