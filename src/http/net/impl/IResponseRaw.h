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
struct IResponseRaw : public IStringViewStash
{
public:
    IResponseRaw() = default;
    ~IResponseRaw();

public:
    void setHeader(const QString& key, const QString& value);

    void setMime(IHttpMime m_mime);
    void setMime(const QString& m_mime);

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

    void setContent(IResponseWare&);
    void setContent(IResponseWare&&);

    void setContent(const QFileInfo& data);

    void setContent(const IHttpInvalidWare& ware);

    void setContent(IResponseContentWare*);

    std::vector<asio::const_buffer> getContent(IRequestImpl&);

public:
    bool m_isValid{true};                           // 标记valid状态，还是放上去了
    QString m_mime;                                 // TODO: 考虑换成 IStringView, 不过这个是之后的事情了
    IHttpStatus m_status {IHttpStatus::OK_200};
    QMultiHash<QString, QString> m_headers;
    std::list<ICookiePart> m_cookies;
    std::list<IResponseContentWare*> m_contents;
};

$PackageWebCoreEnd
