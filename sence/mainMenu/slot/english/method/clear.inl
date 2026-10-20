namespace Gnik_luos {
    void Slot::clear() {   // 字体的释放跟着条目走,不存在外部悬挂指针
        images.clear();
        fonts.clear();
    }
}
