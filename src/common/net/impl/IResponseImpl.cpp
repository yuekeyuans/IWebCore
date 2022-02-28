#include "IResponseImpl.h"
#include "base/IConstantUtil.h"
#include "common/net/impl/IReqRespRaw.h"


$PackageWebCoreBegin

IResponseImpl::IResponseImpl(IReqRespRaw *raw)
{
    this->raw = raw;
}

bool IResponseImpl::respond()
{
    write(generateFirstLine());
    write(generateHeadersContent());
    write(IConstantUtil::NewLine);

    if(raw->m_responseContent.length() != 0 && raw->m_method != IHttpMethod::HEAD){       // 处理 head 方法
        write(raw->m_responseContent);
    }

    flush();
    return true;
}

void IResponseImpl::write(const QByteArray &content)
{
    if(content.length() != 0){
        raw->m_socket->write(content);
    }
}

void IResponseImpl::flush()
{
    raw->m_socket->flush();
}

QByteArray IResponseImpl::generateFirstLine()
{
    QByteArray firstLine;
    firstLine.append(IHttpVersionHelper::toString(raw->m_httpVersion)).append(" ")
        .append(IHttpStatusHelper::toString(raw->m_responseStatus)).append(" ")
        .append(IHttpStatusHelper::toStringDescription(raw->m_responseStatus)).append("\r\n");

    return firstLine;
}

QByteArray IResponseImpl::generateHeadersContent()
{
    auto& headers = raw->m_responseHeaders;

    auto len = raw->m_responseContent.length();
    if(len != 0){
        headers[IHttpHeader::ContentLength] = QString::number(len);

        if(!headers.contains(IHttpHeader::ContentType)){
            headers[IHttpHeader::ContentType] = IHttpMimeHelper::toString(raw->m_responseMime);
        }
    }

    QByteArray headersContent;
    for(auto key : headers.keys()){
        headersContent.append(key).append(": ").append(headers[key]).append(IConstantUtil::NewLine);
    }
    return headersContent;
}

$PackageWebCoreEnd
