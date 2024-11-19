#pragma once

#include "IResponseContentWare.h"

$PackageWebCoreBegin

class IQByteArrayResposneContent : public IResponseContentWare
{
public:
    IQByteArrayResposneContent(QByteArray&&);
    IQByteArrayResposneContent(const QByteArray&);

public:
    virtual int getSize() final;
    virtual const char *getType() final;
    virtual IStringView getContent() final;
    virtual QString getSuggestedMime() final;

private:
    QByteArray m_content;
};

$PackageWebCoreEnd
