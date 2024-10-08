#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/task/ITaskCatagoryInterface.h"

$PackageWebCoreBegin

class IHttpControllerTaskCatagory : public ITaskCatagoryInterface<IHttpControllerTaskCatagory>
{
public:
    virtual const char* $catagory() const final;

public:
    static inline constexpr char CATAGORY[] = "HttpController";
};

$PackageWebCoreEnd
