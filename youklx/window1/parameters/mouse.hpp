namespace youklx {

class Mouse {
public:
    // 当前帧鼠标坐标（逻辑坐标）
    float x{0}, y{0};
    float* 鼠标x{&x};
    float* 鼠标y{&y};
    // 上一帧鼠标坐标
    float xPrev{0}, yPrev{0};
    // 鼠标移动量
    float dx{0}, dy{0};
    float* 移动x{&dx};
    float* 移动y{&dy};

    // 当前按住的按键
    std::unordered_set<int> down;
    // 本帧刚按下
    std::unordered_set<int> pressed;
    // 本帧刚释放
    std::unordered_set<int> released;

    // 本帧滚轮
    float wheelX{0}, wheelY{0};
    float* 滚轮x{&wheelX};
    float* 滚轮y{&wheelY};

public:
    Mouse() = default;

    void beginFrame() {
        xPrev = x;
        dx = 0;
        dy = 0;
        wheelX = 0;
        wheelY = 0;
        pressed.clear();
        released.clear();
    }
    void 开始帧() { beginFrame(); }

    void setPos(float nx, float ny) {
        x = nx;
        y = ny;
    }
    void 设置位置(float nx, float ny) { setPos(nx, ny); }

    void setDown(int button) {
        down.insert(button);
        pressed.insert(button);
    }

    void setUp(int button) {
        down.erase(button);
        released.insert(button);
    }

    void addWheel(float wx, float wy) {
        wheelX += wx;
        wheelY += wy;
    }

    void endFrame() {
        dx = x - xPrev;
        dy = y - yPrev;
    }
    void 结束帧() { endFrame(); }

    // ---- 查询接口 ----
    bool isDown(int button) const {
        return down.find(button) != down.end();
    }
    bool 是否按住(int button) const { return isDown(button); }

    bool isPressed(int button) const {
        return pressed.find(button) != pressed.end();
    }
    bool 是否刚按下(int button) const { return isPressed(button); }

    bool isReleased(int button) const {
        return released.find(button) != released.end();
    }
    bool 是否刚释放(int button) const { return isReleased(button); }
};

} // namespace youklx
