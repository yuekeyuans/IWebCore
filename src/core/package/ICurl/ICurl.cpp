#include "ICurl.h"
#include <QProcess>
#include <QDebug>

ICurl::ICurl(QString url)
{
    m_args.append(url);
}

ICurl &ICurl::b(QString data)
{
    m_args.append( "-b '" + data + "'");
    return *this;
}

ICurl &ICurl::withCookie(QString data)
{
    return b(data);
}

ICurl &ICurl::d(QString data)
{
    m_args.append("-d '" + data + "'");
    return *this;
}

ICurl &ICurl::withPostData(QString data)
{
    return d(data);
}

ICurl &ICurl::withPostDataFile(QString path)
{
    return d("@"+path);
}

ICurl &ICurl::dataUrlencode(QString data)
{
    m_args.append( "--data-urlencode '" + data + "'");
    return *this;
}

ICurl &ICurl::withPostDataUrlEncode(QString data)
{
    return dataUrlencode(data);
}

ICurl &ICurl::F(QString data)
{
    m_args.append( "-F '" + data + "'");
    return *this;
}

ICurl &ICurl::withPostDataMultiPart(QString path, QString fileName, QString type)
{
    QString data = "file=@"+path;
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

ICurl &ICurl::H(QString data)
{
    QString arg = ("-H '" + data + "'");
    m_args.append(arg);
    return *this;
}

ICurl &ICurl::withHeader(QString data)
{
    return H(data);
}

ICurl &ICurl::withHeader(QString key, QString value)
{
    return withHeader(key + ": " + value);
}

ICurl &ICurl::withHeaderContentType(QString data)
{
    return withHeader("Content-Type", data);
}

ICurl &ICurl::limitRate(QString data)
{
    QString arg;
    arg += "--limit-rate " + data;
    m_args.append(arg);
    return *this;
}

ICurl &ICurl::withLimitRate(QString data)
{
    return limitRate(data);
}

ICurl &ICurl::X(QString data)
{
    QString arg;
    arg += "-X " + data;
    m_args.append(arg);
    return *this;
}

ICurl &ICurl::withMethod(QString data)
{
    return X(data);
}


ICurlResponse ICurl::exec()
{
    QProcess process;
    process.start("curl", {"http://www.baidu.com", "-i"});
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
