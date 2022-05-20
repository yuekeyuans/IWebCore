#include "IMultiPart.h"
#include "web/biscuits/IHttpHeader.h"

$PackageWebCoreBegin

// TODO: 这里使用正则式会影响效率，之后再修改吧
// @see https://www.jianshu.com/p/fdb8a1d4893e
// header 当中不能直接传入中文编码，需要进行转码 ||| 好像可以直接传输中文字符进来，
// 具体的支持还需要看 浏览器能否支持，否则还是需要字符编码的。
IMultiPart::IMultiPart()
{
}

void IMultiPart::resolveHeaders()
{
    static QRegularExpression nameExp("name=\"(.*)\"", QRegularExpression::InvertedGreedinessOption);
    static QRegularExpression fileNameExp("filename=\"(.*)\"", QRegularExpression::InvertedGreedinessOption);
    static QRegularExpression charsetExp("charset=(.+)");

    if(headers.contains(IHttpHeader::ContentDisposition)){
        auto disposition = headers[IHttpHeader::ContentDisposition];
        if(disposition.contains("name=")){
            name = nameExp.match(disposition).captured(1);
        }
        if(disposition.contains("filename=")){
            fileName = fileNameExp.match(disposition).captured(1);
        }
    }

    if(headers.contains(IHttpHeader::ContentType)){
        auto contentType = headers[IHttpHeader::ContentType];
        mime = IHttpMimeHelper::toMime(contentType);
        if(contentType.indexOf("charset=") != -1){
            charset = charsetExp.match(contentType).captured(1);
        }
    }

    if(headers.contains(IHttpHeader::ContentTransferEncoding)){
        auto val = headers[IHttpHeader::ContentTransferEncoding];
        if(val == "7bit"){
            encoding = BIT_7;
        }else if(val == "8bit"){
            encoding = BIT_8;
        }else if(val == "binary"){
            encoding = BINARY;
        }else{
            qFatal("error, and this will be removed latter to see whether other type of value");
        }
    }
}

$PackageWebCoreEnd
