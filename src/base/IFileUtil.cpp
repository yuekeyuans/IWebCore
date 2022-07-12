#include "IFileUtil.h"

$PackageWebCoreBegin
int meaningless;

/*!
 * read and return content of QFile file. if fails return empty string.
 * \param file
 * \return
 */
QString IFileUtil::readFile(QFile &file)
{
    if(file.open(QFile::ReadOnly | QFile::Text)){
        return file.readAll();
    }
    return "";
}

/**
 * read and return file of path.
 * @see QString IFileUtil::readFile(QFile& file)
 * @param path
 * @return
 */
QString IFileUtil::readFile(const QString &path)
{
    QFile file(path);
    return readFile(file);
}

bool IFileUtil::isFileExist(const QString &path)
{
    QFileInfo fileInfo(path);
    return fileInfo.exists() && fileInfo.isFile();
}

$PackageWebCoreEnd
