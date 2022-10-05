#include "IApplication.h"

#include "core/configuration/IConfigurationManage.h"
#include "core/task/ITaskManage.h"
#include "core/ICoreAssert.h"

$PackageWebCoreBegin

$UseAssert(ICoreAssert)

namespace IApplicationHelper {
    QStringList fromArguments(int argc, char** argv);
    void printBanner();
}

class IApplicationPrivate{

public:
    QStringList m_arguments;

public:
    static IApplication* m_master;
};

IApplication* IApplicationPrivate::m_master = nullptr;

IApplication::IApplication(int argc, char **argv) : QCoreApplication(argc, argv), d_ptr(new IApplicationPrivate)
{
    Q_D(IApplication);
    d->m_master = this;
    d->m_arguments = IApplicationHelper::fromArguments(argc, argv);
    IApplicationHelper::printBanner();
    ITaskManage::run(d->m_arguments);
}

IApplication *IApplication::theInstance()
{
    if(IApplicationPrivate::m_master == nullptr){
        $Ast->fatal("IApplication_not_created");
    }

    return IApplicationPrivate::m_master;
}

QStringList IApplicationHelper::fromArguments(int argc, char** argv){
    QStringList ret;
    for(int i=0; i<argc; i++){
        QString value = argv[i];
        ret.append(value);
    }
    return ret;
}

void IApplicationHelper::printBanner(){
    auto value = IConfigurationManage::getBanner();
    qInfo().noquote() << value;
}

$PackageWebCoreEnd
