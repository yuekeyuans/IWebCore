#pragma once
#include "base/IHeaderUtil.h"
#include "IResponseInterface.h"
#include "IResponsePreProcessor.h"
$PackageWebCoreBegin

class IStaticFileResponse : public IResponseInterface<IStaticFileResponse>
{
    Q_GADGET
    $AsResponse(IStaticFileResponse)
public:
    using IResponseInterface::operator[];

public:
    IStaticFileResponse();
    IStaticFileResponse(const char* data);
    IStaticFileResponse(const QString& data);
    IStaticFileResponse(IRedirectResponse&& redirectResponse);

    virtual void setInstanceArg(QString &&data) final;
    virtual bool canConvertFromString() final;
    virtual bool matchConvertString(const QString &str) final;
    virtual void updateDelayedResponse() final;

    virtual QSharedPointer<IResponseWare> createInstance() final;

private:
//    QString m_fileName;
    static const QString m_matcherPrefix;
};

IStaticFileResponse operator"" _file(const char* str, size_t size);

$PackageWebCoreEnd
