#pragma once


#pragma once

#include "core/abort/IAbortInterface.h"

$PackageWebCoreBegin

class IBeanAbort : public IAbortInterface<IBeanAbort>
{
    $AsAbort(
        InvalidBeanEmbededBeanType,
        InvalidBeanEmbededPrimitiveType
    )
protected:
    virtual QMap<int, QString> abortDescription() const final{
        return {
            {InvalidBeanEmbededBeanType, "this bean type is not supported as bean field type"},
            {InvalidBeanEmbededPrimitiveType, "this primitive type is not suppoted bean embended type. its not a bean type"}
        };
    }
};

$PackageWebCoreEnd
