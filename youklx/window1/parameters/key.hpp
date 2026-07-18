namespace youklx {

class Keyboard {
public:
    // 当前按住的键
    std::unordered_set<SDL_Keycode> down;
    // 本帧刚按下的键
    std::unordered_set<SDL_Keycode> pressed;
    // 本帧刚释放的键
    std::unordered_set<SDL_Keycode> released;

public:
    Keyboard() = default;

    // 每帧开始：仅清空单帧状态
    void beginFrame() {
        pressed.clear();
        released.clear();
    }

    // 事件循环：键按下
    void setDown(SDL_Keycode key) {
        down.insert(key);
        pressed.insert(key);
    }

    // 事件循环：键释放
    void setUp(SDL_Keycode key) {
        down.erase(key);
        released.insert(key);
    }

    // ---- 查询接口 ----
    bool isDown(SDL_Keycode key) const {
        return down.find(key) != down.end();
    }

    bool isPressed(SDL_Keycode key) const {
        return pressed.find(key) != pressed.end();
    }

    bool isReleased(SDL_Keycode key) const {
        return released.find(key) != released.end();
    }
};

} // namespace youklx
