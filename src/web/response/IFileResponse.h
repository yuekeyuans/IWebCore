#pragma once
#include "core/base/IHeaderUtil.h"
#include "IResponseInterface.h"
#include "IResponsePreProcessor.h"

$PackageWebCoreBegin

class IFileResponse : public IResponseInterface<IFileResponse>
{
    $AsResponse(IFileResponse)
public:
    using IResponseInterface::operator[];

public:
//    IFileResponse();
    using IResponseInterface::IResponseInterface;
    IFileResponse(const char* data);
    IFileResponse(const QString& data);
//    IFileResponse(IRedirectResponse&& redirectResponse);

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
    bool m_enableContentDisposition {true};
};

IFileResponse operator"" _file(const char* str, size_t size);

$PackageWebCoreEnd
