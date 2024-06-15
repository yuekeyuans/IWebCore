#include "ICurl.h"
#include "core/config/IProfileImport.h"

$PackageWebCoreBegin

ICurl::ICurl(const QString& url)
{
    static $QString m_ip{"http.ip"};
    static $UShort m_port{"http.port"};

    m_cmds.append("curl -i");
    m_url = "http://" + m_ip + ":" + QString::number(m_port)  + url;\
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
    m_headerArgs.append("-H \"" + data + "\"");
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
    if(!m_contentType.isEmpty() && m_contentType != contentType){
        qFatal("Content-Type already set");
    }

    m_contentType = contentType;
    return *this;
}

ICurl &ICurl::withJsonBody(const QString &value)
{
    if(m_bodyType != BodyType::None){
        qFatal("body already set");
    }

    withContentType(IHttpMime::APPLICATION_JSON);
    m_bodyArgs.append("-d \"" + value + "\"");
    m_bodyType = BodyType::Json;
    return *this;
}

ICurl &ICurl::withFormData(const QString &value)
{
    if(m_bodyType != BodyType::None && m_bodyType != BodyType::MultiPart){
        qFatal("other data already set");
    }

    withContentType(IHttpMime::MULTIPART_FORM_DATA);
    m_bodyArgs.append("-F \"" + value + "\"");
    return *this;
}

ICurl &ICurl::withFormData(const QString &key, const QString &value)
{
    return withFormData(key + "=" + value);
}

ICurl &ICurl::withFormFile(const QString &name, const QString &path, const QString &fileName, const QString &mime)
{
    QString data = name + "=@"+path;
    if(!fileName.isEmpty()){
        data += ";filename="+fileName;
    }
    if(!mime.isEmpty()){
        data += ";type=" + mime;
    }
    return withFormData(data);
}

ICurl &ICurl::withEncodeData(const QString &value)
{
    if(m_bodyType != BodyType::None && m_bodyType != BodyType::UrlEncoded){
        qFatal("other data already set");
    }

    m_bodyType = BodyType::UrlEncoded;
    withContentType(IHttpMime::APPLICATION_WWW_FORM_URLENCODED);
    m_bodyArgs.append("--data-urlencode \"" + value + "\"");
    return *this;
}

ICurl &ICurl::withBinary(const QString &path, QString mime)
{
    if(m_bodyType != BodyType::None){
        qFatal("other type already set");
    }

    m_bodyType = BodyType::Raw;
    withContentType(mime);
    m_bodyArgs.append("--data-binary \"@" + path + "\"");
    return *this;
}

ICurl &ICurl::withBinary(const QString &path, IHttpMime type)
{
    return withBinary(path, IHttpMimeUtil::toString(type));
}

ICurl &ICurl::withLimitRate(const QString& data)
{
    return withHeader("--limit-rate " + data);
}

ICurlResponse ICurl::exec()
{
    QProcess process;

    QString cmd;
    cmd = m_cmds.join(" ");
    cmd += " " + m_url;
    cmd += " " + m_headerArgs.join(" ");
    if(!m_contentType.isEmpty()){
        cmd += "-H \"Content-Type: " + m_contentType + "\"";
    }

    if(!m_bodyArgs.isEmpty()){
        cmd += " " + m_bodyArgs.join(" ");
    }

    process.start(cmd);
    qDebug().noquote() << cmd;

    process.waitForStarted();
    process.waitForFinished();
    return ICurlResponse(process.readAll());
}

ICurlResponse ICurl::execGet()
{
    m_cmds.append("-X GET");
    return exec();
}

ICurlResponse ICurl::execPost()
{
    m_cmds.append("-X POST");
    return exec();
}

ICurlResponse ICurl::execPut()
{
    m_cmds.append("-X PUT");
    return exec();
}

ICurlResponse ICurl::execDelete()
{
    m_cmds.append("-X DELETE");
    return exec();
}

$PackageWebCoreEnd
