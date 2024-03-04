#pragma once
#include "core/base/IHeaderUtil.h"
#include "IResponseInterface.h"
#include "IResponsePreProcessor.h"

$PackageWebCoreBegin

class IFileResponse : public IResponseInterface<IFileResponse>
{
    Q_GADGET
    $AsResponse(IFileResponse)
public:
    using IResponseInterface::operator[];

    // TODO: 这个后期会调整，但是现在没想好该怎么处理这件事情
    void enableContentDisposition(bool enabled=true);

public:
    IFileResponse();
    IFileResponse(const char* data);
    IFileResponse(const QString& data);
    IFileResponse(IRedirectResponse&& redirectResponse);

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

IFileResponse operator"" _file(const char* str, size_t size);

$PackageWebCoreEnd
