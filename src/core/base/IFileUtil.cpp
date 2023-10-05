#include "IFileUtil.h"
#include "IToeUtil.h"

$PackageWebCoreBegin

$InLine bool IFileUtil::isFileExist(const QString &path)
{
    if(path.startsWith(":")){
        QFileInfo fileInfo(path);
        return fileInfo.exists() && fileInfo.isFile();
    }

    return QFile(path).exists();
}

$InLine QString IFileUtil::readFileAsString(const QString &path, bool *ok)
{
    return readFileAsByteArray(path, ok);
}

$InLine QByteArray IFileUtil::readFileAsByteArray(const QString &path, bool *ok)
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

$InLine QString IFileUtil::getFileSuffix(const QString &path)
{
    return QFileInfo(path).completeSuffix();
}

$PackageWebCoreEnd
