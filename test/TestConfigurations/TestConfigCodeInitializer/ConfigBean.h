#pragma once

#include <IWebCore>

class ConfigBean
{
    Q_GADGET
//    $UseConfig(ConfigBean)
public:
    ConfigBean();

    $AutoWire(QString, name);
    $AutoWire(int, age);
};

