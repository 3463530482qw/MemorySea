#include "vmain.cpp"

int main() {
    try {
        youklx::init();

        image.load("ini/main.ini", "mainMenu");
        image.buildAtlas();

        {
            youklx::Image vimage;
            vimage.load("ini/main.ini", "icon");
            youklx::windowcreateinfo wc;
            wc.loadini("ini/main.ini","windowcreate").load();
            window.iinit("ini/main.ini","windowcreate","acp")
            .create(wc)
            .positionAdjustment()
            .icon(vimage.ima[0][0])
            .ifps("ini/main.ini","windowcreate","fps");
        }

        window.ilstsize("ini/main.ini","windowcreate","sw","sh");
        draw.ilstsize("ini/main.ini","windowcreate","sw","sh");
        vulkan.ilstsize("ini/main.ini","windowcreate","sw","sh");

        vulkan.init(window);

        font.px(100.0f).load("font/LXGWWenKaiLite-Light.ttf");
        vulkan.updateFontTexture(&font);

        scene.ldlli("ini/scene/main.ini","scene");
        scene.ptr = "mainMenu";
        thread.init(window,vulkan,draw,image,font);

        while(window.isrun) {
            if (auto it = scene.dict.find(scene.ptr); it != scene.dict.end()) {
                it->second();
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "异常: " << e.what() << std::endl;
        std::cin.get();
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
