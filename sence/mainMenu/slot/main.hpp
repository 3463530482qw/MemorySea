namespace Gnik_luos {
    class Slot {   // 槽位容器:资源全由 json 添加,代码里不写死任何素材与数量
        public:
            #include "english/available/variable.inl"
        public:
            #include "english/available/function.inl"
            #include "中文/可用/函数.inl"
        private:
            #include "english/available/internal/function.inl"
    };
    using 槽位 = Slot;
}
#include "english/method/load.inl"
#include "english/method/image_batch_load.inl"
#include "english/method/font_batch_load.inl"
#include "english/method/image.inl"
#include "english/method/font.inl"
#include "english/method/clear.inl"
#include "english/method/internal/private_group.inl"
