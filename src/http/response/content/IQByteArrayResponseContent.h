#pragma once

#include "IResponseContentWare.h"

$PackageWebCoreBegin

class IQByteArrayResponseContent : public IResponseContentWare
{
public:
    IQByteArrayResponseContent(QByteArray&&);
    IQByteArrayResponseContent(const QByteArray&);

public:
    virtual int getSize() final;
    virtual IStringView getType() final;
    virtual IStringView getContent() final;
    virtual IStringView getSuggestedMime() final;

private:
    QByteArray m_content;
};

$PackageWebCoreEnd
