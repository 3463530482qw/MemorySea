namespace youklx {

Scene& Scene::remove(const std::string& name) {
    // 如果该场景正在运行，忽略本次移除操作
    if (ptr == name) {
        return *this;
    }

    // 从菜单字典中移除
    dict.erase(name);

    // 查找并释放对应的 DLL 句柄
    auto it = handles.find(name);
    if (it != handles.end()) {
        IC_DLL(it->second);
        handles.erase(it);
    }

    return *this;
}

}
