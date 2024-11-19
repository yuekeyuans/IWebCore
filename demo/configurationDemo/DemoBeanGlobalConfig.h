#pragma once

#include <IWebCore.h>

class DemoBeanGlobalConfig
{
    Q_GADGET
    $ConfigField

public:
    $ValueField(QString, name, name);
    $ValueField(int, age, age)

public:
    DemoBeanGlobalConfig();
};

