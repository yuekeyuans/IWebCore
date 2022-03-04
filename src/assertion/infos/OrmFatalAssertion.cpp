#include "OrmFatalAssertion.h"

$PackageWebCoreBegin

QString IWebCore::OrmFatalAssertion::getAssertInfo()
{
    return R"(
[
    {
        "key" : "orm_view_can_not_be_created",
        "reason": "",
        "description" : "your used orm view is not defined in database, and you do not provide create sql in registerView also",
        "solution" : ""
    }

])";
}

$PackageWebCoreEnd
