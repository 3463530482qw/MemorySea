namespace youklx {
    Agent& Agent::train() {
        size_t N = input.size();
        size_t H = ioput.size();
        size_t O = output.size();

        if (N == 0 || O == 0) return *this;
        if (goal.size() != O) return *this;

        // 预激活值缓存
        std::vector<float> z_in(N);
        std::vector<std::vector<float>> z_hid(H);
        for (size_t h = 0; h < H; ++h) z_hid[h].resize(ioput[h].size());
        std::vector<float> z_out(O);

        // ── 前向传播 ──

        // 输入层
        for (size_t j = 0; j < N; ++j) {
            z_in[j] = input[j] * iweight[j][0] + iweight[j][1];
            cainput[j] = curact(z_in[j]);
        }

        // 隐藏层（全连接）
        for (size_t h = 0; h < H; ++h) {
            size_t L = ioput[h].size();
            if (L == 0) continue;
            auto& prev = (h == 0) ? cainput : caioput[h - 1];
            size_t P = prev.size();
            for (size_t j = 0; j < L; ++j) {
                float sum = 0.0f;
                for (size_t k = 0; k < P; ++k) {
                    sum += prev[k] * ioweight[h][j][k];
                }
                sum += iobias[h][j];
                z_hid[h][j] = sum;
                caioput[h][j] = curact(sum);
            }
        }

        // 输出层（全连接）
        auto& last_hidden = (H > 0) ? caioput[H - 1] : cainput;
        size_t last_size = last_hidden.size();
        if (last_size == 0) return *this;
        for (size_t o = 0; o < O; ++o) {
            float sum = 0.0f;
            for (size_t k = 0; k < last_size; ++k) {
                sum += last_hidden[k] * oweight[o][k];
            }
            sum += obias[o];
            z_out[o] = sum;
            caoutput[o] = curact(sum);
        }

        // ── 反向传播 ──

        // 输出层误差 → 前一层
        std::vector<float> err_buf(last_size, 0.0f);
        for (size_t o = 0; o < O; ++o) {
            float delta = (goal[o] - caoutput[o]) * dcuract(z_out[o]);
            for (size_t k = 0; k < last_size; ++k) {
                oweight[o][k] += lr * delta * last_hidden[k];
                err_buf[k] += delta * oweight[o][k];
            }
            obias[o] += lr * delta;
            if      (obias[o] > 1.0f)  obias[o] -= 0.0001f;
            else if (obias[o] < -1.0f) obias[o] += 0.0001f;
        }

        // 隐藏层反向传播
        for (int h = static_cast<int>(H) - 1; h >= 0; --h) {
            size_t L = ioput[h].size();
            if (L == 0) {
                if (h == 0) err_buf.assign(cainput.size(), err_buf.empty() ? 0.0f : err_buf[0]);
                else        err_buf.assign(caioput[h - 1].size(), err_buf.empty() ? 0.0f : err_buf[0]);
                continue;
            }
            auto& prev = (h == 0) ? cainput : caioput[h - 1];
            size_t P = prev.size();
            std::vector<float> next_err(P, 0.0f);
            for (size_t j = 0; j < L; ++j) {
                float delta = err_buf[j] * dcuract(z_hid[h][j]);
                for (size_t k = 0; k < P; ++k) {
                    ioweight[h][j][k] += lr * delta * prev[k];
                    next_err[k] += delta * ioweight[h][j][k];
                }
                iobias[h][j] += lr * delta;
                if      (iobias[h][j] > 1.0f)  iobias[h][j] -= 0.0001f;
                else if (iobias[h][j] < -1.0f) iobias[h][j] += 0.0001f;
            }
            err_buf = std::move(next_err);
        }

        // 输入层权重更新
        for (size_t j = 0; j < N; ++j) {
            float delta = err_buf[j] * dcuract(z_in[j]);
            iweight[j][0] += lr * delta * input[j];
            iweight[j][1] += lr * delta;
            if      (iweight[j][1] > 1.0f)  iweight[j][1] -= 0.0001f;
            else if (iweight[j][1] < -1.0f) iweight[j][1] += 0.0001f;
        }

        ioput = caioput;
        output = caoutput;
        return *this;
    }
}
