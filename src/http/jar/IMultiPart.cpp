#include "IMultiPart.h"
#include "http/biscuits/IHttpHeader.h"

$PackageWebCoreBegin

// @see https://www.jianshu.com/p/fdb8a1d4893e
// header 当中不能直接传入中文编码，需要进行转码 ||| 好像可以直接传输中文字符进来，
// 具体的支持还需要看 浏览器能否支持，否则还是需要字符编码的。
IMultiPart::IMultiPart()
{
}

IMultiPart::IMultiPart(IStringView view)
{
    auto index = view.find("\r\n\r\n");
    if(index == std::string::npos){
        return;     // invalid
    }
    resolveHeaders(view.substr(0, index));
    content = view.substr(index+4);
}

void IMultiPart::resolveHeaders(IStringView data)
{
    auto lines = data.split(IStringView("\r\n"));
    for(auto line : lines){
        auto index = line.find(":");
        if(index = std::string_view::npos){
            name = {};  // this will cause invalid
            return;
        }
        IStringView key = line.substr(0, index);
        IStringView value = line.substr(index+1).trimmed();

        if(key == IHttpHeader::ContentDisposition){
            static IStringView NAME("name=\"");
            {
                auto index = value.find(NAME);
                if(index != std::string_view::npos){
                    auto args = value.substr(index+NAME.length()).split("\"");   // TODO: unsafe
                    if(args.length() > 1){
                        name = args.first();
                    }
                }
            }

            static IStringView FILE_NAME("filename=\"");
            {
                auto index = value.find(FILE_NAME);
                if(index != std::string_view::npos){
                    auto args = value.substr(index+FILE_NAME.length()).split("\"");   // TODO: unsafe
                    if(args.length() > 1){
                        fileName = args.first();
                    }
                }
            }

        }else if(key == IHttpHeader::ContentType){
            mime = IHttpMimeUtil::toMime(value);
            static IStringView CHARSET("charset=");
            auto index = value.find(CHARSET);
            if(index != std::string_view::npos){
                IStringViewList args = value.substr(index+CHARSET.length()).split(";");   // TODO: unsafe
                if(args.length() >= 1){
                    charset= args.first().trimmed();
                }
            }

        }else if(key ==  IHttpHeader::ContentTransferEncoding){
            if(value == "7bit"){
                encoding = BIT_7;
            }else if(value == "8bit"){
                encoding = BIT_8;
            }else if(value == "binary"){
                encoding = BINARY;
            }else{
                qFatal("error, and this will be removed latter to see whether other type of value");
            }
        }

    }


    // FIXME:
//    static QRegularExpression nameExp("name=\"(.*)\"", QRegularExpression::InvertedGreedinessOption);
//    static QRegularExpression fileNameExp("filename=\"(.*)\"", QRegularExpression::InvertedGreedinessOption);
//    static QRegularExpression charsetExp("charset=(.+)");

//    if(headers.contains(IHttpHeader::ContentDisposition)){
//        auto disposition = headers[IHttpHeader::ContentDisposition];
//        if(disposition.contains("name=")){
//            name = nameExp.match(disposition).captured(1);
//        }
//        if(disposition.contains("filename=")){
//            fileName = fileNameExp.match(disposition).captured(1);
//        }
//    }

//    if(headers.contains(IHttpHeader::ContentType)){
//        auto contentType = headers[IHttpHeader::ContentType];
//        mime = IHttpMimeUtil::toMime(contentType);
//        if(contentType.indexOf("charset=") != -1){
//            charset = charsetExp.match(contentType).captured(1);
//        }
//    }

//    if(headers.contains(IHttpHeader::ContentTransferEncoding)){
//        auto val = headers[IHttpHeader::ContentTransferEncoding];
//        if(val == "7bit"){
//            encoding = BIT_7;
//        }else if(val == "8bit"){
//            encoding = BIT_8;
//        }else if(val == "binary"){
//            encoding = BINARY;
//        }else{
//            qFatal("error, and this will be removed latter to see whether other type of value");
//        }
//    }
}

bool IMultiPart::isValid() const
{
    return !content.empty() && !name.empty();
}

$PackageWebCoreEnd
