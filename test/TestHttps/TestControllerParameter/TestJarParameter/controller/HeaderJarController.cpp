#include "HeaderJarController.h"

QString HeaderJarController::getHeaderJar(IHeaderJar jar)
{
    qDebug() << jar.requestHeaderKeys ();
    return "hello world";
}
