namespace youklx {
    Agent& Agent::init() {
        iact();
        curact = act[funact];
        dcuract = dact[funact];
        std::random_device rd;
        std::mt19937 gen(rd());
        std::normal_distribution<float> dist(0.5f, 0.2005f);
        std::uniform_real_distribution<float> biasDist(-0.5f, 0.5f);
        // 输入层权重 {k, b}
        for (auto& w : iweight) {
            w = {dist(gen), biasDist(gen)};
        }
        // 隐藏层全连接权重
        for (auto& layer : ioweight) {
            for (auto& neuron : layer) {
                for (auto& w : neuron) {
                    w = dist(gen);
                }
            }
        }
        for (auto& layer_bias : iobias) {
            for (auto& b : layer_bias) {
                b = biasDist(gen);
            }
        }
        // 输出层全连接权重
        for (auto& neuron : oweight) {
            for (auto& w : neuron) {
                w = dist(gen);
            }
        }
        for (auto& b : obias) {
            b = biasDist(gen);
        }
        return *this;
    }
    Agent& Agent::iact() {
        act["relu"] = [](float x) { return x > 0.0f ? x : 0.0f; };
        dact["relu"] = [](float x) { return x > 0.0f ? 1.0f : 0.0f; };
        act["leaky"] = [](float x) { return x > 0.0f ? x : 0.01f * x; };
        dact["leaky"] = [](float x) { return x > 0.0f ? 1.0f : 0.01f; };
        act["youk"] = [](float x) {
            return copysignf(3.4f * log10f((2.0f * (1.0f + fabs(x))) / (2.0f + fabs(x))), x);
        };
        dact["youk"] = [](float x) {
            return 1.47659f / ((fabs(x) + 1.0f)*(fabs(x) + 2.0f));
        };
        act["tanh"] = [](float x) { return std::tanh(x); };
        dact["tanh"] = [](float x) { float t = std::tanh(x); return 1.0f - t * t; };
        return *this;
    }
}
