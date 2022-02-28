#include "GlobalConfiguration.h"

QJsonObject GlobalConfiguration::getConfigure() const
{
    QJsonObject obj;
    obj["name"] = "yue";
    return obj;
}
