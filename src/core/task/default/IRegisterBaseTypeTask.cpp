#include "IRegisterBaseTypeTask.h"
#include "IJson.h"

$PackageWebCoreBegin

template<typename T>
void registerBaseType(const QString &name)
{
    qRegisterMetaType<T>(name.toUtf8());
    qRegisterMetaType<T>(QString((name + "&")).toUtf8());
}

void IRegisterBaseTypeTask::$task()
{
    registerBaseType<uchar>("uchar");

    registerBaseType<ushort>("ushort");
    registerBaseType<uint>("unit");
    registerBaseType<ulong>("ulong");
    registerBaseType<qlonglong>("qlonglong");
    registerBaseType<qulonglong>("qulonglong");

    registerBaseType<uint8_t>("uint8_t");
    registerBaseType<int8_t>("int8_t");
    registerBaseType<int16_t>("int16_t");
    registerBaseType<uint16_t>("uint16_t");
    registerBaseType<int32_t>("int32_t");
    registerBaseType<uint32_t>("uint32_t");
    registerBaseType<int64_t>("int64_t");
    registerBaseType<uint64_t>("uint64_t");
}

$PackageWebCoreEnd
