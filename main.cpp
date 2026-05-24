#include "vmain.cpp"

int main() {
    youklx::init(); //初始化库
    {
        youklx::Image image; //建立图像对象
        image.ilpng("ini/main.ini", "icon"); //从iocn标签下加载png图片
        youklx::windowcreateinfo wc; //建立窗口对象
        wc.loadini("ini/main.ini","windowcreate").load(); //从windowcreate加载窗口配置
        window.iinit("ini/main.ini","windowcreate","acp") //从windowcreate加载acp取出宽高比
        .create(wc) //建立窗口
        .positionAdjustment()   //设置窗口位置，默认居中
        .icon(image.ima[0][0]); //加载窗口图标
    }
    Scene.ldlli("ini/scene/main.ini","scene");
    Scene.ptr = "mainMenu";

    while(window.isrun) {
        if (auto it = Scene.dict.find(Scene.ptr); it != Scene.dict.end()) {
            it->second();
        } 
    }
}
