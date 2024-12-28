#include "IRegisterBaseTypeTask.h"
#include "core/bean/IBeanRegisterTypeUnit.h"
#include "IJson.h"

$PackageWebCoreBegin

template<typename T>
void registerBaseType(const QString &name)
{
    qRegisterMetaType<T>(name.toUtf8());
    qRegisterMetaType<T>(QString((name + "&")).toUtf8());
}

// TODO: 这里， 需要测试验证一下是否不用名称注册也能够使用
void IRegisterBaseTypeTask::$task()
{
    registerBaseType<uchar>("uchar");
    registerBaseType<ushort>("ushort");
    registerBaseType<uint>("unit");
    registerBaseType<ulong>("ulong");
    registerBaseType<qlonglong>("qlonglong");
    registerBaseType<qulonglong>("qulonglong");

    IBeanRegisterTypeUnit<short>::registType();
    IBeanRegisterTypeUnit<unsigned short>::registType();
    IBeanRegisterTypeUnit<int>::registType();
    IBeanRegisterTypeUnit<unsigned int>::registType();
    IBeanRegisterTypeUnit<long>::registType();
    IBeanRegisterTypeUnit<unsigned long>::registType();
    IBeanRegisterTypeUnit<long long>::registType();
    IBeanRegisterTypeUnit<unsigned long long>::registType();
    IBeanRegisterTypeUnit<float>::registType();
    IBeanRegisterTypeUnit<double>::registType();

//    IBeanRegisterTypeUnit<IStringView>::registType();
    IBeanRegisterTypeUnit<IString>::registType();
    IBeanRegisterTypeUnit<std::string>::registType();
    IBeanRegisterTypeUnit<QString>::registType();
}

$PackageWebCoreEnd
