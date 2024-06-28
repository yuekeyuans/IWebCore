#include "IApplicationInterface.h"
#include "core/abort/IAbortInterface.h"

$PackageWebCoreBegin

class IApplicationAbort : public IAbortInterface<IApplicationAbort>
{
    $AsAbort(
        IApplicationNotCreated
    )
protected:
    virtual QMap<int, QString> abortDescription() const final{
        return {
            {IApplicationNotCreated, "you can not get any IApplication instance when IApplication not created"}
        };
    }
};

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
        IApplicationAbort::abortIApplicationNotCreated();
    }

    return m_instance;
}

QStringList IApplicationInterface::arguments()
{
    return m_arguments;
}

$PackageWebCoreEnd
