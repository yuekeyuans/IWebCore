#include "ICurlResponse.h"

$PackageWebCoreBegin

ICurlResponse::ICurlResponse(QByteArray data) : m_content(std::move(data))
{
    parse();
    if(m_error){
        qDebug() << "error occured";
    }
}

void ICurlResponse::parse()
{
    if(m_content.isEmpty()){
        return;
    }

    auto index = m_content.indexOf("\r\n\r\n");
    if(index == -1){
        m_error = true;
        return;
    }
    parseHead(m_content.left(index));

    if(!m_error){
        m_body = m_content.mid(index+ 4);
        if(m_headers.contains("Content-Length")){
            if(m_body.length() != m_headers["Content-Length"].toInt()){
                m_error = true;
            }
        }
    }
}

void ICurlResponse::parseHead(QByteArray data)
{
    QStringList content = QString(data).split("\r\n");
    if(content.isEmpty()){
        m_error = true;
        return;
    }
    parseFirstLine(content.first());
    for(int i=1; i<content.length(); i++){
        QStringList pair = QString(content.at(i)).split(":");
        auto value = pair.last().trimmed();
        m_headers[pair.first().trimmed()] = value;
    }
}

void ICurlResponse::parseFirstLine(QString data)
{
    QStringList args = data.split(" ");
    if(args.length() <3){
        m_error = true;
        return;
    }
    m_status = args[1].toInt();
}

$PackageWebCoreEnd
