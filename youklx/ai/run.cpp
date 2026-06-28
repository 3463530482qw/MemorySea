namespace youklx {
    Agent& Agent::run() {
        size_t N = input.size();
        size_t H = ioput.size();
        size_t O = output.size();
        float sum = 0.0f;

        if (N == 0 || O == 0) return *this;

        // 输入层
        for (size_t j = 0; j < N; ++j) {
            cainput[j] = curact(input[j] * iweight[j][0] + iweight[j][1]);
        }

        // 隐藏层（全连接）
        for (size_t h = 0; h < H; ++h) {
            size_t L = ioput[h].size();
            if (L == 0) continue;
            auto& prev = (h == 0) ? cainput : ioput[h - 1];
            size_t P = prev.size();
            for (size_t j = 0; j < L; ++j) {
                sum = 0.0f;
                for (size_t k = 0; k < P; ++k) {
                    sum += prev[k] * ioweight[h][j][k];
                }
                sum += iobias[h][j];
                ioput[h][j] = curact(sum);
            }
        }

        // 输出层（全连接）
        if (H > 0) {
            auto& last_hidden = ioput[H - 1];
            size_t last_size = last_hidden.size();
            if (last_size == 0) return *this;
            for (size_t o = 0; o < O; ++o) {
                sum = 0.0f;
                for (size_t k = 0; k < last_size; ++k) {
                    sum += last_hidden[k] * oweight[o][k];
                }
                sum += obias[o];
                output[o] = curact(sum);
            }
        } else {
            // 无隐藏层，直接从输入到输出
            for (size_t o = 0; o < O; ++o) {
                sum = 0.0f;
                for (size_t k = 0; k < N; ++k) {
                    sum += cainput[k] * oweight[o][k];
                }
                sum += obias[o];
                output[o] = curact(sum);
            }
        }

        return *this;
    }
}
