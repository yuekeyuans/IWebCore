#include "ICurl.h"
#include "core/config/IProfileImport.h"

$PackageWebCoreBegin

ICurl::ICurl(const QString& url)
{
    static $QString m_ip{"http.ip"};
    static $UShort m_port{"http.port"};

    m_args.append("-i");
    m_args.append("http://" + m_ip + ":" + QString::number(m_port)  + url);
}

ICurl &ICurl::b(const QString& data)
{
    m_args.append( "-b '" + data + "'");
    return *this;
}

ICurl &ICurl::withCookie(const QString& data)
{
    return b(data);
}

ICurl &ICurl::d(QString data)
{
    m_args.append("-d \"" + data.toUtf8().toPercentEncoding()+ "\"");
    return *this;
}

ICurl &ICurl::withPostData(const QString& data)
{
    return d(data);
}

ICurl &ICurl::withPostDataFile(const QString &path, IHttpMime mime)
{
    m_args.append("-H Content-Type:" + IHttpMimeUtil::toString(mime));
    m_args.append("--data-binary \"@" + path + "\"");
    return *this;
}

ICurl &ICurl::withPostDataFile(const QString &path, const QString &ContentType)
{
    m_args.append("-H Content-Type:" + ContentType);
    m_args.append("--data-binary \"@" + path + "\"");
    return *this;
}

ICurl &ICurl::dataUrlencode(const QString& data)
{
    m_args.append( "--data-urlencode '" + data + "'");
    return *this;
}

ICurl &ICurl::withPostDataUrlEncode(const QString& data)
{
    return dataUrlencode(data);
}

ICurl &ICurl::F(const QString& data)
{
    m_args.append( "-F '" + data + "'");
    return *this;
}

ICurl &ICurl::withFormData(const QString& key, const QString& value)
{
    return F(key+"="+value);
}

ICurl &ICurl::withFormDataFile(const QString& key, const QString& path, const QString& fileName, const QString& type)
{
    QString data = key + "=@" + path;
    if(!fileName.isEmpty()){
        data.append(";filename="+fileName);
    }
    if(!type.isEmpty()){
        data.append(";type=" + type);
    }
    return F(data);
}

ICurl &ICurl::G()
{
    m_args.append("_G ");
    return *this;
}

ICurl &ICurl::withGenerateUrlQuery()
{
    return G();
}

ICurl &ICurl::H(const QString& data)
{
    const QString& arg = ("-H '" + data + "'");
    m_args.append(arg);
    return *this;
}

ICurl &ICurl::withHeader(const QString& data)
{
    return H(data);
}

ICurl &ICurl::withHeader(const QString& key, const QString& value)
{
    return withHeader(key + ": " + value);
}

ICurl &ICurl::withHeaderContentType(const QString& data)
{
    return withHeader("Content-Type", data);
}

ICurl &ICurl::limitRate(const QString& data)
{
    m_args.append( "--limit-rate " + data);
    return *this;
}

ICurl &ICurl::withLimitRate(const QString& data)
{
    return limitRate(data);
}

ICurl &ICurl::X(const QString& data)
{
    m_args.append("-X " + data);
    return *this;
}

ICurl &ICurl::withMethod(const QString& data)
{
    return X(data);
}


ICurlResponse ICurl::exec()
{
    QProcess process;
    m_args.prepend("curl");
    process.start(m_args.join(" "));

    qDebug().noquote() << m_args.join(" ");

    process.waitForStarted();
    process.waitForFinished();
    return ICurlResponse(process.readAll());
}

ICurlResponse ICurl::execGet()
{
    X("GET");
    return exec();
}

ICurlResponse ICurl::execPost()
{
    X("POST");
    return exec();
}

ICurlResponse ICurl::execPut()
{

    X("PUT");
    return exec();
}

ICurlResponse ICurl::execDelete()
{
    X("DELETE");
    return exec();
}

$PackageWebCoreEnd
