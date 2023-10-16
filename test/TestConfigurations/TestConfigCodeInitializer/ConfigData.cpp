#include "ConfigData.h"

ConfigData::ConfigData()
{

}

QJsonValue ConfigData::getApplicationConfig()
{
    QJsonObject obj;
    obj["hello"] = "world";
    return obj;
}
