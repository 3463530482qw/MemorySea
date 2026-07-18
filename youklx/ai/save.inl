namespace youklx {

    Agent& Agent::save(std::string path) {
        std::filesystem::path filePath(path);
        if (filePath.has_parent_path()) {
            std::filesystem::create_directories(filePath.parent_path());
        }

        std::ofstream out(path, std::ios::binary);
        if (!out.is_open()) {
            std::println("open {} failure",path);
            return *this;
        }

        // 文件头标识
        std::string_view header{"youklx's agent"};
        size_t header_len = header.size();
        out.write(reinterpret_cast<const char*>(&header_len), sizeof(header_len));
        out.write(header.data(), header_len);

        // 学习率
        out.write(reinterpret_cast<const char*>(&lr), sizeof(lr));

        // 激活函数标识
        size_t name_len = funact.size();
        out.write(reinterpret_cast<const char*>(&name_len), sizeof(name_len));
        out.write(funact.c_str(), name_len);

        // 输入层权重 (iweight) —— 保持 {k, b} 格式
        size_t iw_size = iweight.size();
        out.write(reinterpret_cast<const char*>(&iw_size), sizeof(iw_size));
        out.write(reinterpret_cast<const char*>(iweight.data()), iw_size * sizeof(std::array<float, 2>));

        // 隐藏层全连接权重 (ioweight) —— 每层、每神经元、每连接独立保存
        size_t rows = ioweight.size();
        out.write(reinterpret_cast<const char*>(&rows), sizeof(rows));
        for (const auto& layer : ioweight) {
            size_t col_count = layer.size();
            out.write(reinterpret_cast<const char*>(&col_count), sizeof(col_count));
            for (const auto& neuron : layer) {
                size_t w_count = neuron.size();
                out.write(reinterpret_cast<const char*>(&w_count), sizeof(w_count));
                out.write(reinterpret_cast<const char*>(neuron.data()), w_count * sizeof(float));
            }
        }

        // 隐藏层偏置 (iobias)
        size_t bias_rows = iobias.size();
        out.write(reinterpret_cast<const char*>(&bias_rows), sizeof(bias_rows));
        for (const auto& layer_bias : iobias) {
            size_t col_count = layer_bias.size();
            out.write(reinterpret_cast<const char*>(&col_count), sizeof(col_count));
            out.write(reinterpret_cast<const char*>(layer_bias.data()), col_count * sizeof(float));
        }

        // 输出层全连接权重 (oweight) —— 每个输出神经元对前一层有独立权重
        size_t ow_size = oweight.size();
        out.write(reinterpret_cast<const char*>(&ow_size), sizeof(ow_size));
        for (const auto& out_neuron : oweight) {
            size_t w_count = out_neuron.size();
            out.write(reinterpret_cast<const char*>(&w_count), sizeof(w_count));
            out.write(reinterpret_cast<const char*>(out_neuron.data()), w_count * sizeof(float));
        }

        // 输出层偏置 (obias)
        size_t ob_size = obias.size();
        out.write(reinterpret_cast<const char*>(&ob_size), sizeof(ob_size));
        out.write(reinterpret_cast<const char*>(obias.data()), ob_size * sizeof(float));

        out.close();
        return *this;
    }

}
