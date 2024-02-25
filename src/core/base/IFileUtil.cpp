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

inline QString IFileUtil::readFileAsString(const QString &path, bool& ok)
{
    return readFileAsByteArray(path, ok);
}

IResult<QString> IFileUtil::readFileAsString(const QString &path)
{
    bool ok;
    auto content = readFileAsString(path, ok);
    return {content, ok};
}

inline QByteArray IFileUtil::readFileAsByteArray(const QString &path, bool& ok)
{
    QFile file(path);
    if(!file.exists()){
        ok = false;
        return {{}, ok};
    }

    if(file.open(QFile::ReadOnly)){
        auto content = file.readAll();
        file.close();
        ok = true;
        return content;
    }
    ok = false;
    return {};
}

IResult<QByteArray> IFileUtil::readFileAsByteArray(const QString &path)
{
    bool ok;
    auto value = readFileAsByteArray(path, ok);
    return {value, ok};
}

inline QString IFileUtil::getFileSuffix(const QString &path)
{
    return QFileInfo(path).completeSuffix();
}

$PackageWebCoreEnd
