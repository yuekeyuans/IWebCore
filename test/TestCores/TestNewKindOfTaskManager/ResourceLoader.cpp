#include "ResourceLoader.h"

QString ResourceLoader::name() const
{
    return IMetaUtil::getTypename<ResourceLoader>();
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
