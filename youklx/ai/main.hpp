namespace youklx {
    class Agent {
        public:
            std::vector<float> input;
            std::vector<std::vector<float>> ioput;
            std::vector<float> output;
            std::vector<float> goal;
            std::vector<float> cainput;
            std::vector<std::vector<float>> caioput;
            std::vector<float> caoutput;
        public:
            std::vector<std::array<float,2>> iweight;
            std::vector<std::vector<std::vector<float>>> ioweight;  // 全连接权重 [层][神经元][前层连接]
            std::vector<std::vector<float>> iobias;                  // 隐藏层偏置 [层][神经元]
            std::vector<std::vector<float>> oweight;                 // 输出层权重 [输出][前层连接]
            std::vector<float> obias;                                // 输出层偏置 [输出]
            float lr{0.2};
        public:
            std::string funact{"youk"};
            std::function<float(float)> curact;
            std::unordered_map<std::string, std::function<float (float)>> act{};
            std::function<float(float)> dcuract;
            std::unordered_map<std::string, std::function<float (float)>> dact{};
        public:
            Agent& iact();
            Agent& init(); 
            Agent& snet(const std::vector<float>& setnet);
            Agent& sgo(std::vector<float>&& setgoal);
            Agent& sin(std::vector<float>&& setinput);
            Agent& sfunact(std::string_view setfunact);
            Agent& save(std::string path);
            Agent& load(std::string path);
            Agent& run();
            Agent& train();
    };
}
#include "init.cpp"
#include "snet.cpp"
#include "sgo.cpp"
#include "sin.cpp"
#include "sfunact.cpp"
#include "save.cpp"
#include "load.cpp"
#include "run.cpp"
#include "train.cpp"