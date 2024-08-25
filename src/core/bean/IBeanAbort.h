#pragma once


#pragma once

#include "core/abort/IAbortInterface.h"

$PackageWebCoreBegin

class IBeanAbort : public IAbortInterface<IBeanAbort>
{
    $AsAbort(
        invalid_bean_field_type,
        invalid_bean_embended_type
    )
protected:
    virtual QMap<int, QString> abortDescription() const final{
        return {
            {invalid_bean_field_type, "this type is not supported bean field type"},
            {invalid_bean_embended_type, "this type is not suppoted bean embended type. its not a bean type"}
        };
    }
};

$PackageWebCoreEnd
