namespace youklx {

class Mouse {
public:
    // 当前帧鼠标坐标（逻辑坐标）
    float x{0}, y{0};
    // 上一帧鼠标坐标
    float xPrev{0}, yPrev{0};
    // 鼠标移动量
    float dx{0}, dy{0};

    // 当前按住的按键
    std::unordered_set<int> down;
    // 本帧刚按下
    std::unordered_set<int> pressed;
    // 本帧刚释放
    std::unordered_set<int> released;

    // 本帧滚轮
    float wheelX{0}, wheelY{0};

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

    void setPos(float nx, float ny) {
        x = nx;
        y = ny;
    }

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

    // ---- 查询接口 ----
    bool isDown(int button) const {
        return down.find(button) != down.end();
    }
    bool isPressed(int button) const {
        return pressed.find(button) != pressed.end();
    }
    bool isReleased(int button) const {
        return released.find(button) != released.end();
    }

    bool leftDown()     const { return isDown(SDL_BUTTON_LEFT); }
    bool leftPressed()  const { return isPressed(SDL_BUTTON_LEFT); }
    bool leftReleased() const { return isReleased(SDL_BUTTON_LEFT); }

    bool middleDown()     const { return isDown(SDL_BUTTON_MIDDLE); }
    bool middlePressed()  const { return isPressed(SDL_BUTTON_MIDDLE); }
    bool middleReleased() const { return isReleased(SDL_BUTTON_MIDDLE); }

    bool rightDown()     const { return isDown(SDL_BUTTON_RIGHT); }
    bool rightPressed()  const { return isPressed(SDL_BUTTON_RIGHT); }
    bool rightReleased() const { return isReleased(SDL_BUTTON_RIGHT); }
};

} // namespace youklx