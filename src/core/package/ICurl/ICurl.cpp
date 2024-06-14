#include "ICurl.h"
#include "core/config/IProfileImport.h"

$PackageWebCoreBegin

ICurl::ICurl(const QString& url)
{
    static $QString m_ip{"http.ip"};
    static $UShort m_port{"http.port"};

    m_headers.append("-i");
    m_headers.append("http://" + m_ip + ":" + QString::number(m_port)  + url);
}


ICurl &ICurl::withPathArg(const QString &data)
{
    m_pathArgs.append(data);
    return *this;
}

ICurl &ICurl::withPathArg(const QString &name, const QString &value)
{
    return withPathArg(name + "="+value);
}

ICurl &ICurl::withPathArgs(QMap<QString, QString> args)
{
    auto keys = args.keys();
    for(auto key : keys){
        withPathArg(key, args[key]);
    }
    return *this;
}

ICurl &ICurl::withHeader(const QString& data)
{
    m_headers.append("-H \"" + data + "\"");
    return *this;
}

ICurl &ICurl::withHeader(const QString& key, const QString& value)
{
    return withHeader(key + ": " + value);
}

ICurl &ICurl::withContentType(IHttpMime mime)
{
    return withContentType(IHttpMimeUtil::toString(mime));
}

ICurl &ICurl::withContentType(const QString &contentType)
{
    return withHeader("Content-Type", contentType);
}

ICurl &ICurl::withLimitRate(const QString& data)
{
    return withHeader("--limit-rate " + data);
}

ICurlResponse ICurl::exec()
{
    QProcess process;
    m_headers.prepend("curl");
    process.start(m_headers.join(" "));

    qDebug().noquote() << m_headers.join(" ");

    process.waitForStarted();
    process.waitForFinished();
    return ICurlResponse(process.readAll());
}

ICurlResponse ICurl::execGet()
{
    m_headers.append("-X GET");
    return exec();
}

ICurlResponse ICurl::execPost()
{
    m_headers.append("-X POST");
    return exec();
}

ICurlResponse ICurl::execPut()
{
    m_headers.append("-X PUT");
    return exec();
}

ICurlResponse ICurl::execDelete()
{
    m_headers.append("-X DELETE");
    return exec();
}

$PackageWebCoreEnd
