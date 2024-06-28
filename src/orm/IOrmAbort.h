#pragma once

#include "core/abort/IAbortInterface.h"

$PackageWebCoreBegin

class IOrmAbort : public IAbortInterface<IOrmAbort>
{
    $AsAbort(
        where_sql_start_with_OR,
        OrmViewCantCreatetd
    )
protected:
    virtual QMap<int, QString> abortDescription() const final{
        return {
            {where_sql_start_with_OR, "your where sql start with OR, please check your code"},
            {OrmViewCantCreatetd, "your used orm view is not defined in database, and you do not provide create sql in registerView also"}
        };
    }
};

$PackageWebCoreEnd
