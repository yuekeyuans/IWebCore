#include "OrmWarnAssertion.h"

$PackageWebCoreBegin

QString OrmWarnAssertion::getAssertInfo()
{
    return R"(
[
    {
        "key" : "where_sql_start_with_OR",
        "reason": "",
        "description" : "your where sql start with OR, please check your code",
        "solution" : ""
    },
    {
        "key" : "where_sql_start_with_NOT",
        "reason": "",
        "description" : "where clause can not start with NOT",
        "solution" : ""
    }


])";
}

$PackageWebCoreEnd
