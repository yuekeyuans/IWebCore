#pragma once

#include "IResponseContentWare.h"

$PackageWebCoreBegin

class IFileResponseContent : public IResponseContentWare
{
public:
    IFileResponseContent(const QString& path);

public:
    virtual int getSize() final;
    virtual IStringView getType() final;
    virtual IStringView getContent() final;
    virtual IStringView getSuggestedMime() final;

private:
    QString m_path;
    QByteArray m_content;
};

$PackageWebCoreEnd
