namespace youklx {

Scene& Scene::clear() {
    // 清空当前场景指针
    ptr.clear();

    // 清空菜单字典
    dict.clear();

    // 释放所有 DLL 句柄并清空
    for (auto& [name, handle] : handles) {
        IC_DLL(handle);
    }
    handles.clear();

    return *this;
}

}
