#include "IOrmAssert.h"

$PackageWebCoreBegin

void IOrmAssert1::loadAssert()
{

    addFatal("orm_view_can_not_be_created"
             , "your used orm view is not defined in database, and you do not provide create sql in registerView also");

    addWarn("where_sql_start_with_OR", "your where sql start with OR, please check your code");

    addWarn("where_sql_start_with_NOT", "where clause can not start with NOT");
}

$PackageWebCoreEnd
