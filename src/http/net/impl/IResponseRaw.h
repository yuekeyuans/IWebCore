#pragma once
#include "core/util/IHeaderUtil.h"
#include "http/biscuits/IHttpMime.h"
#include "http/biscuits/IHttpStatus.h"
#include "http/net/ICookiePart.h"
#include "http/response/content/IResponseContentWare.h"
#include "http/invalid/IHttpInvalidWare.h"

$PackageWebCoreBegin

class IRequestImpl;
struct IResponseRaw
{
public:
    IResponseRaw() = default;
    ~IResponseRaw();

public:
    void setMime(IHttpMime m_mime);
    void setMime(const QString& m_mime);

    void setContent(std::string&& data);
    void setContent(const std::string& data);

    void setContent(QString&& data);
    void setContent(const QString& data);

    void setContent(QByteArray&& data);
    void setContent(const QByteArray& data);
    void setContent(const char* data);

    void setContent(const QFileInfo& data);

    void setContent(const IHttpInvalidWare& ware);

    void setContent(IResponseContentWare*);

    std::vector<asio::const_buffer> getContent(IRequestImpl&);

public:
    QString m_mime;
    IHttpStatus m_status {IHttpStatus::OK_200};
    QMultiHash<QString, QString> m_headers;
    std::list<ICookiePart> m_cookies;
    std::list<IResponseContentWare*> m_contents;

private:
    std::vector<QByteArray> m_store;    // TODO: 这里用 stash 代替
};

$PackageWebCoreEnd
