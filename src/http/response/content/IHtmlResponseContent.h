#pragma once

#include "IResponseContentWare.h"

$PackageWebCoreBegin

// TODO: 之后考虑优化的事情
class IHtmlResponseContent : public IResponseContentWare
{
public:
    IHtmlResponseContent(QByteArray&&);
    IHtmlResponseContent(const QByteArray&);
    IHtmlResponseContent(const QString&);
    IHtmlResponseContent(const std::string& value);

public:
    virtual int getSize() final;
    virtual const char *getType() final;
    virtual IStringView getContent() final;
    virtual QString getSuggestedMime() final;

private:
    QByteArray m_content;
};

$PackageWebCoreEnd

