namespace youklx {
    class Plpng {
        public:
            unsigned char* data{nullptr};
            int w{0};
            int h{0};
            int channels{4};
            int desired_channels{4};
            std::string lable{"png"};
    };
}