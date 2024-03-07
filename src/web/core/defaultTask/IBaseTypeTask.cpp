#include "IBaseTypeTask.h"
#include "core/base/MetaUtil.h"

$PackageWebCoreBegin


// this won't be compile in Qt5 gcc , so comment it out.

void IBaseTypeTask::task()
{
    IMetaUtil::registerBaseType<short>("short");
    IMetaUtil::registerBaseType<ushort>("ushort");
    IMetaUtil::registerBaseType<int>("int");
    IMetaUtil::registerBaseType<uint>("unit");
    IMetaUtil::registerBaseType<long>("long");
    IMetaUtil::registerBaseType<ulong>("ulong");
    IMetaUtil::registerBaseType<qlonglong>("qlonglong");
    IMetaUtil::registerBaseType<qulonglong>("qulonglong");
    IMetaUtil::registerBaseType<float>("float");
    IMetaUtil::registerBaseType<double>("double");

    IMetaUtil::registerBaseType<int16_t>("int16_t");
    IMetaUtil::registerBaseType<uint16_t>("uint16_t");
    IMetaUtil::registerBaseType<int32_t>("int32_t");
    IMetaUtil::registerBaseType<uint32_t>("uint32_t");
    IMetaUtil::registerBaseType<int64_t>("int64_t");
    IMetaUtil::registerBaseType<uint64_t>("uint64_t");

    IMetaUtil::registerBaseType<QString>("QString");
    IMetaUtil::registerBaseType<QByteArray>("QByteArray");
    IMetaUtil::registerBaseType<QJsonValue>("QJsonValue");
    IMetaUtil::registerBaseType<QJsonArray>("QJsonArray");
    IMetaUtil::registerBaseType<QJsonObject>("QJsonObject");
}

$PackageWebCoreEnd