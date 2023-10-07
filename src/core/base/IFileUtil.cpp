#include "IFileUtil.h"
#include "IToeUtil.h"

$PackageWebCoreBegin

inline bool IFileUtil::isFileExist(const QString &path)
{
    if(path.startsWith(":")){
        QFileInfo fileInfo(path);
        return fileInfo.exists() && fileInfo.isFile();
    }

    return QFile(path).exists();
}

inline QString IFileUtil::readFileAsString(const QString &path, bool *ok)
{
    return readFileAsByteArray(path, ok);
}

inline QByteArray IFileUtil::readFileAsByteArray(const QString &path, bool *ok)
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

inline QString IFileUtil::getFileSuffix(const QString &path)
{
    return QFileInfo(path).completeSuffix();
}

$PackageWebCoreEnd
