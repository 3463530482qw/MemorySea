namespace youklx {
    class Plpng {
        public:
            unsigned char* data{nullptr};   //图片数据
            int w{0};   //图片宽
            int h{0};   //图片高
            int channels{4};    //图片通道
            int desired_channels{4};    //图片目标通道
            std::string lable{"png"};   //图片类型
    };
}