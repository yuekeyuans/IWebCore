#include "IFileUtil.h"
#include "IToeUtil.h"

$PackageWebCoreBegin

bool IFileUtil::isFileExist(const QString &path)
{
    if(path.startsWith(":")){
        QFileInfo fileInfo(path);
        return fileInfo.exists() && fileInfo.isFile();
    }

    return QFile(path).exists();
}

QString IFileUtil::readFileAsString(const QString &path, bool& ok)
{
    return readFileAsByteArray(path, &ok);
}

IResult<QString> IFileUtil::readFileAsString(const QString &path)
{
    bool ok;
    auto content = readFileAsString(path, ok);
    if(ok){
        return content;
    }
    return std::nullopt;
}

QByteArray IFileUtil::readFileAsByteArray(const QString &path, bool* ok)
{
    QFile file(path);
    if(!file.exists() || !file.open(QFile::ReadOnly)){
        IToeUtil::setOk(ok, false);
        return {};
    }

    QByteArray content = file.readAll();
    file.close();
    IToeUtil::setOk(ok, true);
    return content;
}


QString IFileUtil::getFileSuffix(const QString &path)
{
    return QFileInfo(path).completeSuffix();
}

void IFileUtil::assertWhenFileInvalid(const QString &path)
{
    QFile file(path);
    if(!file.exists()){
        qWarning() << "file not exist";
    }
    if(!file.open(QFile::ReadOnly)){
        qWarning() << "file can not be opened";
    }
    file.close();
}

$PackageWebCoreEnd
