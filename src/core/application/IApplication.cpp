#include "IApplication.h"

#include "core/context/IContextManage.h"
#include "core/task/ITaskManage.h"
#include "core/ICoreAssert.h"

$PackageWebCoreBegin

$UseAssert(ICoreAssert)

namespace IApplicationHelper {
    QStringList fromArguments(int argc, char** argv);
}

class IApplicationPrivate{

public:
    QStringList m_arguments;

public:
    static IApplication* m_master;
};

IApplication* IApplicationPrivate::m_master = nullptr;

IApplication::IApplication()
    : IApplication(0, nullptr)
{
}

IApplication::IApplication(int argc, char **argv)
    : QCoreApplication(argc, argv), d_ptr(std::make_shared<IApplicationPrivate>())
{
    Q_D(IApplication);
    d->m_master = this;
    d->m_arguments = IApplicationHelper::fromArguments(argc, argv);
    ITaskManage::run();
}

IApplication *IApplication::theInstance()
{
    if(IApplicationPrivate::m_master == nullptr){
        $Ast->fatal("IApplication_not_created");
    }

    return IApplicationPrivate::m_master;
}

QStringList IApplication::arguments()
{
    auto d_ptr = IApplication::theInstance()->d_func();
    return d_ptr->m_arguments;
}

QStringList IApplicationHelper::fromArguments(int argc, char** argv){
    QStringList ret;
    for(int i=0; i<argc; i++){
        QString value = argv[i];
        ret.append(value);
    }
    return ret;
}

$PackageWebCoreEnd
