#pragma once

#include "IResponseContentWare.h"

$PackageWebCoreBegin

class IQStringResponseContent : public IResponseContentWare
{
public:
    IQStringResponseContent(QString&&);
    IQStringResponseContent(const QString&);

public:
    virtual int getSize() final;
    virtual IStringView getType() final;
    virtual IStringView getContent() final;
    virtual IStringView getSuggestedMime() final;

private:
    QString m_content;
    QByteArray m_rawData;
};

$PackageWebCoreEnd
