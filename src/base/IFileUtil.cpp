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

QString IFileUtil::normalizeFilePath(QString path, bool*ok)
{
    if(path.contains('\\')){
        path.replace('\\', '/');
    }

    while(path.contains("//")){
        path.replace("//", "/");
    }

    if(path.contains("../")){               // 预防路径中出现 ../ 的情况
        auto pieces = path.split("/");
        auto index = pieces.indexOf("..");
        if(index == 0){
            IToeUtil::setOk(ok, false);
            return path;
        }
        pieces.removeAt(index);
        pieces.removeAt(index-1);
        path = pieces.join("/");
    }

    IToeUtil::setOk(ok, true);
    return path;
}

$PackageWebCoreEnd
