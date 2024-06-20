#include "IMultiPart.h"
#include "http/biscuits/IHttpHeader.h"
#include "http/net/IRequest.h"
#include "http/invalid/IHttpBadRequestInvalid.h"

$PackageWebCoreBegin

// TODO: 这个需要重新考虑一下
static void resolveHeaders(IStringView data, IRequest* request, IMultiPart* part)
{
    auto lines = data.split(IStringView("\r\n"));
    int lineLength = lines.length();
    for(int i=0; i<lineLength; i++){
        auto line = lines[i];
        if(i+1<lineLength && lines[i+1][0] == ' '){
            QByteArray array = line.toQByteArray() + lines[i+1].toQByteArray().trimmed();
            lines[i+1] = IStringView(); // 清空下一条数据
            line = request->stash(array);
        }

        auto index = line.find_first_of(':');
        if(index == std::string_view::npos){
            part->name = {};  // this will cause invalid
            return;
        }
        IStringView key = line.substr(0, index).trimmed();
        IStringView value = line.substr(index+1).trimmed();

        if(key == IHttpHeader::ContentDisposition){
            static IStringView NAME("name=\"");
            {
                auto index = value.find(NAME);
                if(index != std::string_view::npos){
                    auto args = value.substr(index+NAME.length()).split("\"");   // TODO: unsafe
                    if(args.length() > 1){
                        part->name = args.first();
                    }
                }
            }

            static IStringView FILE_NAME("filename=\"");
            {
                auto index = value.find(FILE_NAME);
                if(index != std::string_view::npos){
                    auto args = value.substr(index+FILE_NAME.length()).split("\"");   // TODO: unsafe
                    if(args.length() > 1){
                        part->fileName = args.first();
                    }
                }
            }

        }else if(key == IHttpHeader::ContentType){
            part->mime = IHttpMimeUtil::toMime(value);
            static IStringView CHARSET("charset=");
            auto index = value.find(CHARSET);
            if(index != std::string_view::npos){
                IStringViewList args = value.substr(index+CHARSET.length()).split(";");   // TODO: unsafe
                if(args.length() >= 1){
                    part->charset= args.first().trimmed();
                }
            }
        }else if(key ==  IHttpHeader::ContentTransferEncoding){
            if(value == "7bit"){
                part->encoding = IMultiPart::BIT_7;
            }else if(value == "8bit"){
                part->encoding = IMultiPart::BIT_8;
            }else if(value == "binary"){
                part->encoding = IMultiPart::BINARY;
            }else{
                qFatal("error, and this will be removed latter to see whether other type of value");
            }
        }
    }
}

IMultiPart::IMultiPart(IStringView view, IRequest* request)
{
    auto index = view.find("\r\n\r\n");
    if(index == std::string_view::npos){
        request->setInvalid(IHttpBadRequestInvalid("multipart has no headers"));
        return;
    }
    resolveHeaders(view.substr(0, index), request, this);
    content = view.substr(index+4);
}

bool IMultiPart::isValid() const
{
    return !content.empty() && !name.empty();
}


$PackageWebCoreEnd
