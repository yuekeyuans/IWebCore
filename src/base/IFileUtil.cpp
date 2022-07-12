#include "IFileUtil.h"
#include "IToeUtil.h"

$PackageWebCoreBegin
int meaningless;

bool IFileUtil::isFileExist(const QString &path)
{
    QFileInfo fileInfo(path);
    return fileInfo.exists() && fileInfo.isFile();
}

QString IFileUtil::readFileAsString(const QString &path, bool *ok)
{
    return readFileAsByteArray(path, ok);
}

QByteArray IFileUtil::readFileAsByteArray(const QString &path, bool *ok)
{
    QFile file(path);
    if(file.open(QFile::ReadOnly)){
        IToeUtil::setOk(ok, true);
        auto content = file.readAll();
        file.close();
        return content;
    }

    IToeUtil::setOk(ok, false);
    return {};
}

$PackageWebCoreEnd
