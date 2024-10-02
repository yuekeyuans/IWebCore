#pragma once


#pragma once

#include "core/abort/IAbortInterface.h"

$PackageWebCoreBegin

class IBeanAbort : public IAbortInterface<IBeanAbort>
{
    $AsAbort(
        InvalidFieldType,
        ToJsonMethodNotExist,
        LoadJsonMethodNotExist
    )
protected:
    virtual QMap<int, QString> abortDescription() const final{
        return {
            {InvalidFieldType, "this field type is not supported"},
            {ToJsonMethodNotExist, "toJson method of one field not exist, please check it"},
            {LoadJsonMethodNotExist, "loadJson method of one field not exist, please check it"},
        };
    }
};

$PackageWebCoreEnd
