#include "IAssertInfoList.h"

#ifdef QT_DEBUG

#include "infos/ConfigurationAssertion.h"
#include "infos/ControllerFatalAssertion.h"
#include "infos/ControllerWarnAssertion.h"
#include "infos/DeferRegisterNotAllowedFatal.h"
#include "infos/configuration/ConfigurationMayNotInitializedAssert.h"

#include "infos/OrmFatalAssertion.h"
#include "infos/OrmWarnAssertion.h"

#endif

$PackageWebCoreBegin

IAssertInfoList::IAssertInfoList()
{
    init();
}

void IAssertInfoList::init()
{
#ifdef QT_DEBUG
    static std::once_flag flag;
    std::call_once(flag, [](){
        ConfigurationAssertion::instance();
        ControllerFatalAssertion::instance();
        ControllerWarnAssertion::instance();
        DeferRegisterNotAllowedFatal::instance();
        ConfigurationMayNotInitializedAssert::instance();
        OrmFatalAssertion::instance();
        OrmWarnAssertion::instance();
    });
#endif
}

$PackageWebCoreEnd
