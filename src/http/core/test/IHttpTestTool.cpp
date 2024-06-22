#include "IHttpTestTool.h"

$PackageWebCoreBegin

QString IHttpTestTool::createRandomFile(QString fileName, int fileSize)
{
    QString exeDir = QCoreApplication::applicationDirPath();
    if(fileName.isEmpty()){
        fileName = QTime::currentTime().toString("hhmmss") + ".txt";
    }
    QString filePath = QDir(exeDir).filePath(fileName);

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning("Could not open file for writing.");
        return filePath;
    }
    QByteArray data;
    data.fill('A', fileSize); // 使用字符 'A' 填充到指定大小
    file.write(data);
    file.close();

    return filePath;
}

$PackageWebCoreEnd
