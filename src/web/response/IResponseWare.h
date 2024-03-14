#pragma once

#include "core/base/IHeaderUtil.h"
#include "web/biscuits/IHttpMime.h"
#include "web/biscuits/IHttpStatus.h"
#include "IResponseContent.h"

$PackageWebCoreBegin

struct IResponseWareRaw;
class IRedirectResponse;

class IResponseWare
{
public:
    IResponseWare();
    virtual ~IResponseWare();

    QString& operator[](const QString& header);

    const QString& mime() const;
    void setMime(IHttpMime);
    
    IHttpStatus status() const;
    void setStatus(IHttpStatus statusCode);

    const QMap<QString, QString>& headers() const;
    void setHeader(const QString& key, const QString& value);

    virtual void setContent(const QByteArray& bytes);
    virtual void setContent(const QString& content);
    virtual void setContent(const char* content);
    virtual void setInvalid(IHttpStatus, const QString& reason);
    IResponseContent& getContent();

    virtual void setInstanceArg(QString &&data); // 强制使用右值引用，为了在代码当中保持参数传入 std::move 增强标记性
    virtual void setInstanceArg(void *arg, const QString &tag = "");
    virtual void setInstanceCopy(IResponseWare* interface_);

    void redirectTo(IRedirectResponse&& redirectResponse);

    virtual bool canConvertFromString();
    virtual bool matchConvertString(const QString&);

    virtual QSharedPointer<IResponseWare> createInstance();

protected:
    IResponseWareRaw* raw{nullptr};
};

$PackageWebCoreEnd
