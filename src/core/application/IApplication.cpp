#include "IApplication.h"

#include "core/task/ITaskManage.h"
#include "core/assert/IGlobalAssert.h"

$PackageWebCoreBegin

$UseGlobalAssert()

namespace detail
{
    static QStringList fromArguments(int argc, char** argv);
    static int args = 0;
}

class IApplicationImpl
{
public:
    QStringList m_arguments;
    static IApplication* s_master;
};

IApplication* IApplicationImpl::s_master = nullptr;

IApplication::IApplication()
    : QCoreApplication(detail::args, nullptr), d_ptr(std::make_shared<IApplicationImpl>())
{
    d_ptr->s_master = this;
    ITaskManage::run();
}

IApplication::IApplication(int argc, char **argv)
    : QCoreApplication(argc, argv), d_ptr(std::make_shared<IApplicationImpl>())
{
    d_ptr->m_arguments = detail::fromArguments(argc, argv);
    d_ptr->s_master = this;
    ITaskManage::run();
}

IApplication::~IApplication()
{

}

const IApplication *IApplication::theInstance()
{
    if(IApplicationImpl::s_master == nullptr){
        $GlobalAssert->fatal("IApplication_not_created");
    }

    return IApplicationImpl::s_master;
}

const QStringList& IApplication::arguments()
{
    auto d_ptr = IApplication::theInstance()->d_ptr;
    return d_ptr->m_arguments;
}

QStringList detail::fromArguments(int argc, char** argv){
    QStringList ret;
    for(int i=0; i<argc; i++){
        ret.append(argv[i]);
    }

    return ret;
}

$PackageWebCoreEnd
