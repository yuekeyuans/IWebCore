#include "ResourceLoader.h"

ResourceLoader::ResourceLoader()
{

}

QString ResourceLoader::name()
{
    return "Resource loader";
}

QStringList ResourceLoader::orders()
{
    return {};
}

void ResourceLoader::task()
{
    qDebug() << "hello world";
}

QString ResourceLoader::catagory()
{
    return "resource";
}
