namespace youklx {
    Agent& Agent::snet(const std::vector<float>& setnet) {
        int H = setnet.size() - 2;    // 隐藏层层数
        int O_idx = setnet.size() - 1; // 输出层在 setnet 中的索引

        input.resize(setnet[0]);
        cainput.resize(setnet[0]);

        ioput.resize(H);
        caioput.resize(H);
        for (int h = 0; h < H; ++h) {
            ioput[h].resize(setnet[h + 1] < 1.0f ? 1 : int(setnet[h + 1]));
            caioput[h].resize(setnet[h + 1] < 1.0f ? 1 : int(setnet[h + 1]));
        }

        output.resize(setnet[O_idx]);
        caoutput.resize(setnet[O_idx]);
        goal.resize(setnet[O_idx]);

        iweight.resize(setnet[0]);

        // 全连接隐藏层权重：每层每个神经元对上一层所有神经元各有一个权重
        ioweight.resize(H);
        iobias.resize(H);
        for (int h = 0; h < H; ++h) {
            int P = setnet[h];  // 前一层大小（h=0为输入层，h>0为上一层隐藏层）
            ioweight[h].resize(setnet[h + 1]);
            iobias[h].resize(setnet[h + 1]);
            for (auto& neuron_weights : ioweight[h]) {
                neuron_weights.resize(P);
            }
        }

        // 输出层全连接权重：每个输出神经元对最后隐藏层所有神经元各有一个权重
        int last_hidden = (H > 0) ? setnet[H] : setnet[0];
        oweight.resize(setnet[O_idx]);
        obias.resize(setnet[O_idx]);
        for (auto& out_weights : oweight) {
            out_weights.resize(last_hidden);
        }

        return *this;
    }
}
