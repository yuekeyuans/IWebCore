#include <IWebCore>

IConfigInstance(ConfigSpecificDemo, configGroup){
    QJsonObject obj ={
        {"name" , "zhi"},
        {"age", 102}
    };
    return obj;
}
