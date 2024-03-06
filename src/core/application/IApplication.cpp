#include "IApplication.h"

#include "core/task/ITaskManage.h"
#include "core/assert/IGlobalAssert.h"

$PackageWebCoreBegin

$UseGlobalAssert()

namespace IApplicationHelper
{
    QStringList fromArguments(int argc, char** argv);
    static int args = 0;
}

class IApplicationPrivate
{
public:
    QStringList m_arguments;
    static IApplication* s_master;
};

IApplication* IApplicationPrivate::s_master = nullptr;

IApplication::IApplication()
    : QCoreApplication(IApplicationHelper::args, nullptr), d_ptr(std::make_shared<IApplicationPrivate>())
{
    Q_D(IApplication);
    d->s_master = this;
    ITaskManage::run();
}

IApplication::IApplication(int argc, char **argv)
    : QCoreApplication(argc, argv), d_ptr(std::make_shared<IApplicationPrivate>())
{
    Q_D(IApplication);
    d->m_arguments = IApplicationHelper::fromArguments(argc, argv);
    d->s_master = this;
    ITaskManage::run();
}

IApplication::~IApplication()
{

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
