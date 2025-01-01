#pragma once

#include "IHttpPath.h"

$PackageWebCoreBegin

struct IHttpPathDetail : public IHttpPath
{
public:
    IHttpPathDetail(const QStringList& args);
private:
    void checkMappingUrl();
    void checkMappingUrlErrorCommon(const QString &piece);
    void CheckMappingUrlErrorWildCard(const QString& piece);
    bool isPieceWildCard(const QString &piece);
};

$PackageWebCoreEnd


