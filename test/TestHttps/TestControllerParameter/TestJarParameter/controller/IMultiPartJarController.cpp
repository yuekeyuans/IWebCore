#include "IMultiPartJarController.h"

QString IMultiPartJarController::getMultiPartJar(IMultiPartJar jar)
{
    qDebug() << jar.getRequestMultiPartNames ();
    auto fileParts = jar.getRequestFileMultiParts ();
    for(const auto& part : fileParts){
        QFile file(part.fileName);
        file.open (QFile::WriteOnly);
        file.write (part.content);
        file.close ();
    }
    return "hello world";
}
