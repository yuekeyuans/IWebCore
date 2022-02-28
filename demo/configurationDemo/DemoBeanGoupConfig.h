#pragma once

#include <QtCore>
#include <IWebCore.h>

class DemoBeanGoupConfig
{
    Q_GADGET
    $ConfigField

public:
    $ValueField(QString, name, configGroup, name)

    $Value(int, age, configGroup, age);
    int age;

public:
    DemoBeanGoupConfig();
};

