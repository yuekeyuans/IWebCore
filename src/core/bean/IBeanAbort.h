#pragma once


#pragma once

#include "core/abort/IAbortInterface.h"

$PackageWebCoreBegin

class IBeanAbort : public IAbortInterface<IBeanAbort>
{
    $AsAbort(
        InvalidBeanEmbededBeanType,
        InvalidBeanEmbededPrimitiveType,
        ToJsonMethodNotExist,
        LoadJsonMethodNotExist
    )
protected:
    virtual QMap<int, QString> abortDescription() const final{
        return {
            {InvalidBeanEmbededBeanType, "this bean type is not supported as bean field type"},
            {InvalidBeanEmbededPrimitiveType, "this primitive type is not suppoted bean embended type. its not a bean type"},
            {ToJsonMethodNotExist, "toJson method of one field not exist, please check it"},
            {LoadJsonMethodNotExist, "loadJson method of one field not exist, please check it"},
        };
    }
};

$PackageWebCoreEnd
