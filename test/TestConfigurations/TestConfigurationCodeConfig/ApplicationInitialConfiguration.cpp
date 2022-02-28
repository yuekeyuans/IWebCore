#include "ApplicationInitialConfiguration.h"

ApplicationInitialConfiguration::ApplicationInitialConfiguration()
{

}

QJsonObject ApplicationInitialConfiguration::getConfigure() const
{
    QJsonObject obj;
    obj["hello"] = "world";
    return obj;
}
