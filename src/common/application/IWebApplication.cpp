#include "IWebApplication.h"

#include "common/task/ITaskManage.h"
#include "configuration/IConfigurationManage.h"

$PackageWebCoreBegin

namespace IWebApplicationHelper {
    QStringList fromArguments(int argc, char** argv);
    void printBanner();
}

IWebApplication::IWebApplication(int argc, char **argv) : QCoreApplication(argc, argv)
{
    m_arguments = IWebApplicationHelper::fromArguments(argc, argv);
    IWebApplicationHelper::printBanner();
    ITaskManage::run(m_arguments);
}

QStringList IWebApplication::getArguments() const
{
    return m_arguments;
}

QStringList IWebApplicationHelper::fromArguments(int argc, char** argv){
    QStringList ret;
    for(int i=0; i<argc; i++){
        QString value = argv[i];
        ret.append(value);
    }
    return ret;
}

void IWebApplicationHelper::printBanner(){
    auto value = IConfigurationManage::getBanner();
    qDebug().noquote() << value;
}

$PackageWebCoreEnd
