#include "IApplication.h"

#include "core/configuration/IConfigurationManage.h"
#include "core/task/ITaskManage.h"

$PackageWebCoreBegin

namespace IApplicationHelper {
    QStringList fromArguments(int argc, char** argv);
    void printBanner();
}

IApplication::IApplication(int argc, char **argv) : QCoreApplication(argc, argv)
{
    m_arguments = IApplicationHelper::fromArguments(argc, argv);
    IApplicationHelper::printBanner();
    ITaskManage::run(m_arguments);
}

const QStringList &IApplication::getArguments()
{
    return m_arguments;
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
