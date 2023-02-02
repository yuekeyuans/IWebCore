#pragma once
#include "core/base/IHeaderUtil.h"
#include "IResponseInterface.h"
#include "IResponsePreProcessor.h"
$PackageWebCoreBegin

class IStaticFileResponse : public IResponseInterface<IStaticFileResponse>
{
    Q_GADGET
    $AsResponse(IStaticFileResponse)
public:
    using IResponseInterface::operator[];

    // TODO: 这个后期会调整，但是现在没想好该怎么处理这件事情
    void enableContentDisposition(bool enabled=true);

public:
    IStaticFileResponse();
    IStaticFileResponse(const char* data);
    IStaticFileResponse(const QString& data);
    IStaticFileResponse(IRedirectResponse&& redirectResponse);

    void setFilePath(const QString& path);

protected:
    virtual void setContent(const QByteArray& bytes) final;
    virtual void setContent(const QString& content) final;
    virtual void setContent(const char* content) final;

    virtual void setInstanceArg(QString &&data) final;
    virtual bool canConvertFromString() final;
    virtual bool matchConvertString(const QString &str) final;

    virtual QSharedPointer<IResponseWare> createInstance() final;

private:
    static const QString m_matcherPrefix;
    bool m_enableContentDisposition{false};
};

IStaticFileResponse operator"" _file(const char* str, size_t size);

$PackageWebCoreEnd
