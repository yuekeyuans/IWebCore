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
    registerBaseType<std::string>("std::string");
    registerBaseType<IJson>("IJson");
    registerBaseType<bool>("bool");
    registerBaseType<char>("char");
    registerBaseType<uchar>("uchar");

    registerBaseType<short>("short");
    registerBaseType<ushort>("ushort");
    registerBaseType<int>("int");
    registerBaseType<uint>("unit");
    registerBaseType<long>("long");
    registerBaseType<ulong>("ulong");
    registerBaseType<qlonglong>("qlonglong");
    registerBaseType<qulonglong>("qulonglong");
    registerBaseType<float>("float");
    registerBaseType<double>("double");

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
