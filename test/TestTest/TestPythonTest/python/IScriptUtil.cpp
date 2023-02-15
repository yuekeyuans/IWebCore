#include "IScriptUtil.h"


void IScriptUtil::copyScript()
{
    auto entries = QDir(":/python").entryInfoList();

    auto path = qApp->applicationDirPath() + "/python/";

    for(const QFileInfo& entry : entries){
        QFile(entry.absoluteFilePath()).copy(path + entry.fileName());
        qDebug() << entry << path;
    }

}

void IScriptUtil::execScript()
{
    static QProcess process;
    auto path = qApp->applicationDirPath() + "/python/";
    process.setWorkingDirectory(path);
    qDebug() << "pwd" << process.workingDirectory();
    process.execute("python " + path + "TestDemo.py");
}
