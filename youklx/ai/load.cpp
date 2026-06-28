namespace youklx {

    Agent& Agent::load(std::string path) {
        std::ifstream in(path, std::ios::binary);
        if (!in.is_open()) return *this;

        // 读取并验证文件头
        std::string_view expected_header{"youklx's agent"};
        size_t header_len;
        in.read(reinterpret_cast<char*>(&header_len), sizeof(header_len));
        if (header_len != expected_header.size()) {
            in.close();
            return *this;
        }
        std::string file_header(header_len, '\0');
        in.read(file_header.data(), header_len);
        if (file_header != expected_header) {
            in.close();
            return *this;
        }

        in.read(reinterpret_cast<char*>(&lr), sizeof(lr));

        size_t name_len;
        in.read(reinterpret_cast<char*>(&name_len), sizeof(name_len));
        funact.resize(name_len);
        in.read(&funact[0], name_len);

        // 输入层权重 (iweight)
        size_t iw_size;
        in.read(reinterpret_cast<char*>(&iw_size), sizeof(iw_size));
        iweight.resize(iw_size);
        in.read(reinterpret_cast<char*>(iweight.data()), iw_size * sizeof(std::array<float, 2>));

        // 隐藏层全连接权重 (ioweight)
        size_t rows;
        in.read(reinterpret_cast<char*>(&rows), sizeof(rows));
        ioweight.resize(rows);
        for (auto& layer : ioweight) {
            size_t col_count;
            in.read(reinterpret_cast<char*>(&col_count), sizeof(col_count));
            layer.resize(col_count);
            for (auto& neuron : layer) {
                size_t w_count;
                in.read(reinterpret_cast<char*>(&w_count), sizeof(w_count));
                neuron.resize(w_count);
                in.read(reinterpret_cast<char*>(neuron.data()), w_count * sizeof(float));
            }
        }

        // 隐藏层偏置 (iobias)
        size_t bias_rows;
        in.read(reinterpret_cast<char*>(&bias_rows), sizeof(bias_rows));
        iobias.resize(bias_rows);
        for (auto& layer_bias : iobias) {
            size_t col_count;
            in.read(reinterpret_cast<char*>(&col_count), sizeof(col_count));
            layer_bias.resize(col_count);
            in.read(reinterpret_cast<char*>(layer_bias.data()), col_count * sizeof(float));
        }

        // 输出层全连接权重 (oweight)
        size_t ow_size;
        in.read(reinterpret_cast<char*>(&ow_size), sizeof(ow_size));
        oweight.resize(ow_size);
        for (auto& out_neuron : oweight) {
            size_t w_count;
            in.read(reinterpret_cast<char*>(&w_count), sizeof(w_count));
            out_neuron.resize(w_count);
            in.read(reinterpret_cast<char*>(out_neuron.data()), w_count * sizeof(float));
        }

        // 输出层偏置 (obias)
        size_t ob_size;
        in.read(reinterpret_cast<char*>(&ob_size), sizeof(ob_size));
        obias.resize(ob_size);
        in.read(reinterpret_cast<char*>(obias.data()), ob_size * sizeof(float));

        in.close();

        // 从权重维度推导网络结构，还原所有结构向量
        input.resize(iweight.size());
        cainput.resize(iweight.size());

        ioput.resize(rows);
        caioput.resize(rows);
        for (size_t i = 0; i < rows; ++i) {
            ioput[i].resize(ioweight[i].size());
            caioput[i].resize(ioweight[i].size());
        }

        output.resize(oweight.size());
        goal.resize(oweight.size());
        caoutput.resize(oweight.size());

        iact();
        sfunact(funact);
        return *this;
    }

}
