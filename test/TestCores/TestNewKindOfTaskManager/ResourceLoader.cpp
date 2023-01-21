#include "ResourceLoader.h"

QString ResourceLoader::name() const
{
    return "Resource loader";
}

QStringList ResourceLoader::orders() const
{
    return {};
}

QString ResourceLoader::catagory() const
{
    return "resource";
}

void ResourceLoader::task()
{
    qDebug() << "hello world";
}
