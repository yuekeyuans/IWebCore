#pragma once

#include "core/base/IStringViewStash.h"
#include "core/util/IHeaderUtil.h"
#include "http/biscuits/IHttpMime.h"
#include "http/biscuits/IHttpStatus.h"
#include "http/net/ICookiePart.h"
#include "http/response/content/IResponseContentWare.h"

$PackageWebCoreBegin

class IRequestImpl;
class IResponseWare;
class IHttpInvalidWare;
class IResponseRaw : public IStringViewStash
{
    friend class IRequestImpl;
public:
    IResponseRaw() = default;
    ~IResponseRaw();

public:
    void setHeader(const QString& key, const QString& value);

    void setMime(IHttpMime m_mime);
    void setMime(IStringData&&);

    void setContent(IJson&& data);
    void setContent(const IJson& data);

    void setContent(std::string&& data);
    void setContent(const std::string& data);

    void setContent(QString&& data);
    void setContent(const QString& data);

    void setContent(QByteArray&& data);
    void setContent(const QByteArray& data);
    void setContent(const char* data);

    void setContent(IStringView data);

    void setContent(const QFileInfo& data);
    void setContent(const IHttpInvalidWare& ware);
    void setContent(IResponseContentWare*);

private:
    void setResponseWare(IResponseWare&&);
    void setResponseWare(IResponseWare&);

public:
    std::vector<asio::const_buffer> getContent(IRequestImpl&);

public:
    bool m_isValid{true};
    IStringData m_mime;
    IHttpStatus m_status {IHttpStatus::OK_200};
    QMultiHash<QString, QString> m_headers;
    std::list<ICookiePart> m_cookies;
    std::list<IResponseContentWare*> m_contents;
};

$PackageWebCoreEnd
