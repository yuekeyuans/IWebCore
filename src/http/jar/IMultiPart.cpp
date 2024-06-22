#include "IMultiPart.h"
#include "http/biscuits/IHttpHeader.h"
#include "http/invalid/IHttpBadRequestInvalid.h"
#include "http/net/IRequest.h"

$PackageWebCoreBegin

namespace detail
{
    void resolveHeaders(IMultiPart* self, IStringView data, IRequest* request);
    IStringViewList concatenateHeaders(const IStringViewList& list, IRequest* request);
}

IMultiPart::IMultiPart(IStringView view, IRequest* request)
{
    auto index = view.find("\r\n\r\n");
    if(index == std::string_view::npos){
        request->setInvalid(IHttpBadRequestInvalid("multipart has no headers"));
        return;
    }

    content = view.substr(index+4);
    detail::resolveHeaders(this, view.substr(0, index), request);
}

bool IMultiPart::isValid() const
{
    return !content.empty() && !name.empty();
}

static IStringView FORMDATE_NAME("name=\"");
static IStringView FORMDATA_FILE_NAME("filename=\"");
static IStringView FORMDATA_CHARSET("charset=");
void detail::resolveHeaders(IMultiPart* self, IStringView data, IRequest* request)
{
    auto lines = detail::concatenateHeaders(data.split(IStringView("\r\n")), request);
    for(auto line : lines){
        auto index = line.find_first_of(':');
        if(index == std::string_view::npos){
            request->setInvalid(IHttpBadRequestInvalid("multipart header error without colon"));
            return;
        }
        IStringView key = line.substr(0, index).trimmed();
        IStringView value = line.substr(index+1).trimmed();

        if(key == IHttpHeader::ContentDisposition){
            auto index = value.find(FORMDATE_NAME);
            if(index != std::string_view::npos){
                self->name = value.substr(index+FORMDATE_NAME.length());
                if(!self->name.empty() && self->name.startWith("\"")){
                    self->name = self->name.substr(1, self->name.length()-2);
                }
            }
            index = value.find(FORMDATA_FILE_NAME);
            if(index != std::string_view::npos){
                self->fileName = value.substr(index+FORMDATA_FILE_NAME.length());
                if(!self->fileName.empty() && self->fileName.startWith("\"")){
                    self->fileName = self->fileName.substr(1, self->fileName.length()-2);
                }
            }

        }else if(key == IHttpHeader::ContentType){
            self->mime = IHttpMimeUtil::toMime(value);
            auto index = value.find(FORMDATA_CHARSET);
            if(index != std::string_view::npos){
                IStringViewList args = value.substr(index+FORMDATA_CHARSET.length()).split(";");
                if(args.length() >= 1){
                    self->charset= args.first().trimmed();
                }
            }
        }else if(key ==  IHttpHeader::ContentTransferEncoding){
            if(value == "7bit"){
                self->encoding = IMultiPart::BIT_7;
            }else if(value == "8bit"){
                self->encoding = IMultiPart::BIT_8;
            }else if(value == "binary"){
                self->encoding = IMultiPart::BINARY;
            }else{
                request->setInvalid(IHttpBadRequestInvalid("multipart header error with ContentTransferEncoding"));
            }
        }
    }
}

IStringViewList detail::concatenateHeaders(const IStringViewList& list, IRequest* request){
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


$PackageWebCoreEnd
