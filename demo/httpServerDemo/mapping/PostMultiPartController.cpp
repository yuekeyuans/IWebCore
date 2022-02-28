#include "PostMultiPartController.h"

PostMultiPartController::PostMultiPartController()
{
    $ConstructController
}

QString PostMultiPartController::fun1(IMultiPart name)
{
    qDebug() << name.name << name.content;
    return name.name;
}

QString PostMultiPartController::fun2(IMultiPart name)
{
    qDebug() << name.name << name.content;
    return name.content;
}

QString PostMultiPartController::fun3(IMultiPart name)
{
    auto fileName = name.fileName;
    QFile file(fileName);
    file.open(QFile::WriteOnly);
    file.write(name.content);
    file.close();
    return QString::number(name.content.length());
}

QString PostMultiPartController::funMultiPart(IMultiPart name)
{
    qDebug() << name.name;
    name.name = "no-Name";
    return name.content;
}

QString PostMultiPartController::funMultiPartRef(IMultiPart &name)
{
    qDebug() << name.name;
    name.name = "no-Name";
    return name.content;
}
