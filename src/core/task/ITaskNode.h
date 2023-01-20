#pragma once

#include "base/IHeaderUtil.h"

$PackageWebCoreBegin

struct ITaskNode
{
public:
    using FunType = std::function<void()>;
    enum class Mode{
        Catagory,
        Task,
    };

public:
    FunType function;

    Mode mode;
    QString name;
    QString catagory;   // if mode == Catagory, default empty.
    QStringList orders; // orders of sorting regulation.
};

$PackageWebCoreEnd
