std::unordered_map<std::string, Font*> data;   // 名字 → 字体对象指针(外部注册的字体生命周期归注册方,仓库只登记)
std::vector<std::unique_ptr<Font>> owned;        // iload 创建的字体(仓库拥有,随仓库销毁)
std::vector<std::string> owned_names;            // iload 登记的字体名(热更新时先按名注销)
