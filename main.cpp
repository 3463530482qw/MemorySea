#include "vmain.cpp"

int main() {
    youklx::init(); //初始化库
    image.ilpng("ini/main.ini", "mainMenu");
    {
        youklx::Image vimage; //建立图像对象
        vimage.ilpng("ini/main.ini", "icon"); //从iocn标签下加载png图片
        youklx::windowcreateinfo wc; //建立窗口对象
        wc.loadini("ini/main.ini","windowcreate").load(); //从windowcreate加载窗口配置
        window.iinit("ini/main.ini","windowcreate","acp") //从windowcreate加载acp取出宽高比
        .create(wc) //建立窗口
        .positionAdjustment()   //设置窗口位置，默认居中
        .icon(vimage.ima[0][0]) //加载窗口图标
        .ifps("ini/main.ini","windowcreate","fps"); //从windowcreate加载fps取出目标帧率
    }
    window.ilstsize("ini/main.ini","windowcreate","sw","sh");
    draw.ilstsize("ini/main.ini","windowcreate","sw","sh");
    vulkan.ilstsize("ini/main.ini","windowcreate","sw","sh");
    vulkan.init(window); //初始化vulkan
    font.px(100.0f).load("font/LXGWWenKaiLite-Light.ttf");
    vulkan.updateFontTexture(&font);
    
    scene.ldlli("ini/scene/main.ini","scene");
    scene.ptr = "mainMenu";
    while(window.isrun) {
        if (auto it = scene.dict.find(scene.ptr); it != scene.dict.end()) {
            it->second();
        } 
    }
}
