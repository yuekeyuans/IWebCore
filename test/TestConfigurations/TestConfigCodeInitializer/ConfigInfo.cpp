#include "base/IContextTaskInterface"


//IConfigInstance(ConfigSpecificDemo){
//    QJsonObject obj ={
//        {"name" , "zhi"},
//        {"age", 102}
//    };
//    return obj;
//}

class ConfigDemo : public IContextTaskInterface<ConfigDemo, true>
{
    $UseInstance(ConfigDemo)
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
