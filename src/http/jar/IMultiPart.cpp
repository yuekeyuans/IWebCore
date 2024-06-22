#include "IMultiPart.h"
#include "http/biscuits/IHttpHeader.h"
#include "http/invalid/IHttpBadRequestInvalid.h"
#include "http/net/IRequest.h"

$PackageWebCoreBegin

namespace detail
{
    IStringViewList concatenateHeaders(const IStringViewList& list, IRequest* request){
        IStringViewList ret;
        if(list.empty()){
            return ret;
        }

        int length = list.length();
        for(int i=length-1; i>=0; i--){
            auto view = list[i];
            for(; view[0]==' '; ){
                i--;
                if(i==-1){
                    request->setInvalid(IHttpBadRequestInvalid("multipart header error"));
                    return {};
                }
                view = request->stash(list[i].toQByteArray() + view.toQByteArray().trimmed());
            }
            ret.append(view);
        }
        return ret;
    }
}

IMultiPart::IMultiPart(IStringView view, IRequest* request)
{
    auto index = view.find("\r\n\r\n");
    if(index == std::string_view::npos){
        request->setInvalid(IHttpBadRequestInvalid("multipart has no headers"));
        return;
    }
    content = view.substr(index+4);
    resolveHeaders(view.substr(0, index), request);
}

bool IMultiPart::isValid() const
{
    return !content.empty() && !name.empty();
}

static IStringView FORMDATE_NAME("name=\"");
static IStringView FORMDATA_FILE_NAME("filename=\"");
void IMultiPart::resolveHeaders(IStringView data, IRequest* request)
{
    auto lines = detail::concatenateHeaders(data.split(IStringView("\r\n")), request);
    for(auto line : lines){
        auto index = line.find_first_of(':');
        if(index == std::string_view::npos){
            name = {};
            return;
        }
        IStringView key = line.substr(0, index).trimmed();
        IStringView value = line.substr(index+1).trimmed();

        if(key == IHttpHeader::ContentDisposition){
            auto index = value.find(FORMDATE_NAME);
            if(index != std::string_view::npos){
                auto args = value.substr(index+FORMDATE_NAME.length()).split("\"");   // TODO: unsafe
                if(args.length() > 1){
                    name = args.first();
                }
            }
            index = value.find(FORMDATA_FILE_NAME);
            if(index != std::string_view::npos){
                auto args = value.substr(index+FORMDATA_FILE_NAME.length()).split("\"");   // TODO: unsafe
                if(args.length() > 1){
                    fileName = args.first();
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
                encoding = IMultiPart::BIT_7;
            }else if(value == "8bit"){
                encoding = IMultiPart::BIT_8;
            }else if(value == "binary"){
                encoding = IMultiPart::BINARY;
            }else{
                qFatal("error, and this will be removed latter to see whether other type of value");
            }
        }
    }
}


$PackageWebCoreEnd
