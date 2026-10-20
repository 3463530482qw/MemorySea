namespace Gnik_luos {
    bool Slot::private_group(const simdjson::dom::element& json, std::string_view group, simdjson::dom::object& body) {   // 没写这一段就当空表
        simdjson::dom::object root{};
        if (json.get_object().get(root)) {
            throw std::runtime_error("Slot::private_group => JSON is not an object");
        }
        simdjson::dom::element resource{};
        if (root.at_key("resource").get(resource) || !resource.is_object()) {
            return false;
        }
        simdjson::dom::object groups{};
        if (resource.get_object().get(groups) || groups.at_key(group).get_object().get(body)) {
            return false;
        }
        return true;
    }
}
