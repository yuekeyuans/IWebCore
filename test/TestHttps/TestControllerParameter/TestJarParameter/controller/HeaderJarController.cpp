#include "HeaderJarController.h"

QString HeaderJarController::getHeaderJar(IHeaderJar jar)
{
    bool ok;
    return jar.getRequestHeaderValue ("hello", &ok);
}

QString HeaderJarController::testRequestHeaderKeys(const IHeaderJar &jar)
{
    return IConvertUtil::toString (jar.requestHeaderKeys ());
}

QString HeaderJarController::testAddResponseHeader(IHeaderJar &jar)
{
    jar.setResponseHeader ("hello", "world");
    return "hello";
}
