#include "IApplication.h"

#include "core/config/IContextManage.h"
#include "core/task/ITaskManage.h"
#include "core/assert/IGlobalAssert.h"

$PackageWebCoreBegin

$UseGlobalAssert()

namespace IApplicationHelper
{
    QStringList fromArguments(int argc, char** argv);
}

class IApplicationPrivate
{
public:
    QStringList m_arguments;
    static IApplication* s_master;
};
IApplication* IApplicationPrivate::s_master = nullptr;

IApplication::IApplication()
    : IApplication(0, nullptr)
{
}

IApplication::IApplication(int argc, char **argv)
    : QCoreApplication(argc, argv), d_ptr(std::make_shared<IApplicationPrivate>())
{
    Q_D(IApplication);
    d->s_master = this;
    d->m_arguments = IApplicationHelper::fromArguments(argc, argv);
    ITaskManage::run();
}

const IApplication *IApplication::theInstance()
{
    if(IApplicationPrivate::s_master == nullptr){
        $GlobalAssert->fatal("IApplication_not_created");
    }

    return IApplicationPrivate::s_master;
}

const QStringList& IApplication::arguments()
{
    auto d_ptr = IApplication::theInstance()->d_func();
    return d_ptr->m_arguments;
}

QStringList IApplicationHelper::fromArguments(int argc, char** argv){
    QStringList ret;
    for(int i=0; i<argc; i++){
        ret.append(argv[i]);
    }

    return ret;
}

$PackageWebCoreEnd
