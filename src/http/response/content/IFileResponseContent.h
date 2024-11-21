#pragma once

#include "IResponseContentWare.h"

$PackageWebCoreBegin

class IFileResponseContent : public IResponseContentWare
{
public:
    IFileResponseContent(const QString& path);

public:
    virtual int getSize() final;
    virtual const char *getType() final;
    virtual IStringView getContent() final;
    virtual QString getSuggestedMime() final;

private:
    QString m_path;
    QByteArray m_content;
};

$PackageWebCoreEnd
