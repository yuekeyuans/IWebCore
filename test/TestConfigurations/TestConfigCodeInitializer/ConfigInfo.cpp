#include "base/IContextTaskInterface"


//IConfigInstance(ConfigSpecificDemo){
//    QJsonObject obj ={
//        {"name" , "zhi"},
//        {"age", 102}
//    };
//    return obj;
//}

// TODO: 这里 Application Config 没有返回自己的 path

class ConfigDemo : public IContextTaskInterface<ConfigDemo, true>
{
    $AsContext(ConfigDemo)
public:
    ConfigDemo() = default;
    virtual QJsonValue getApplicationConfig() final{
            QJsonObject obj ={
                {"name" , "zhi"},
                {"age", 102}
            };
            return obj;
    }
};
