#include "IApplicationInterface.h"
#include "core/assert/IGlobalAssert.h"

$PackageWebCoreBegin

$UseGlobalAssert()

IApplicationInterface* IApplicationInterface::m_instance = nullptr;

IApplicationInterface::IApplicationInterface(int arg, char **argv)
{
    for(int i=0; i<arg; i++){
        m_arguments.append(QString::fromLocal8Bit(argv[i]));
    }
}

IApplicationInterface *IApplicationInterface::instance()
{
    if(!m_instance){
        $GlobalAssert->fatal("IApplication_not_created");
    }

    return m_instance;
}

QStringList IApplicationInterface::arguments()
{
    return m_arguments;
}

$PackageWebCoreEnd
