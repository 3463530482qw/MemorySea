# 工作规范
变量命名采用纯小写,应当避免大写.多个单词可用下划线链接.格式 单词_单词

跨模块变量定义到vmain,vmode

wiall用于#include标准头文件,第三方库,自定义大类,除了wiall其它地方静止#include标准头文件,第三方库等

->,**写法如无必要应该进行避免,如 this->变量名 视为低质量代码

无论函数和类型应当做到一个函数一个文件,文件名同函数.除了强关联的函数如load(加载) iload(通过ini加载)外视为不合格交付.

单文件推荐长度不超过200到300行,100行内为最佳.

工作记录和报告写在.vscode/work_cache.txt,写完之后记得清理,最好在500行以内.

如果犯错了可以在本文件内进行添加记录保证不会再犯.

# 类标准定义
include parameters(用到的数据结构体或子类)
namespace youklx {
    class 类型名 {
        public:
            #include"en/api/var.inl"
            #include"中文/接口/变量.inl"
        public:
            #include"en/api/function.inl"
            #include"中文/接口/函数.inl"
        private:
            #include"en/api/internal/var.inl"
            #include"en/api/internal/function.inl"
        public:
            构建函数
            析构函数
    };
    using 中文类型名 = 类型名;
}
include 函数实现

注:此结构为完整结构,可以进行省略,但额外添加视为错误.