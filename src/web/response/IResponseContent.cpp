#include "IResponseContent.h"

$PackageWebCoreBegin

int IResponseContent::length()
{
    switch (type) {
    case String:
        return contentString.length();
    case Bytes:
        return contentBytes.length();
    case File:
        return QFileInfo(contentFilePath).size();
    }
    return 0;
}

$PackageWebCoreEnd
