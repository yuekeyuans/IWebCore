#pragma once

#include "base/IHeaderUtil.h"
#include "web/biscuits/IHttpMime.h"
#include "web/biscuits/IHttpStatus.h"
#include "IResponseContent.h"

$PackageWebCoreBegin

struct IResponseWareRaw;
class IRedirectResponse;


class IResponseWare{
    $AsWare
public:
    IResponseWare();
    virtual ~IResponseWare();

    QString& operator[](const QString& header);

    QString mime() const;
    IHttpStatus status() const;
//    size_t contentLength() const;

    IResponseContent& getContent();

//    QByteArray& content();   // TODO: need const constrait?
    const QMap<QString, QString>& headers() const;

    void setMime(IHttpMime);
    void setStatus(IHttpStatus statusCode);
    void setHeader(const QString& key, const QString& value);
    void setContent(const QByteArray& bytes);
    void setContent(const QString& content);
    void setContent(const char* content);

    void redirectTo(IRedirectResponse&& redirectResponse);

    virtual void setInstanceArg(QString &&data); // 强制使用右值引用，为了在代码当中保持参数传入 std::move 增强标记性
    virtual void setInstanceArg(void *arg, const QString &tag = "");
    virtual void setInstanceCopy(IResponseWare* interface);

    virtual bool canConvertFromString();
    virtual bool matchConvertString(const QString&);

    virtual QSharedPointer<IResponseWare> createInstance();

protected:
    IResponseWareRaw* raw{nullptr};
};

$PackageWebCoreEnd
