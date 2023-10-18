#pragma once

#include "IContextApplicationConfigInterface"

using namespace IWebCore;

class ConfigData : public IContextApplicationConfigInterface<ConfigData>
{
    Q_GADGET
    $UseInstance(ConfigData)
public:
    ConfigData();

public:
    virtual QJsonValue getApplicationConfig();

};

