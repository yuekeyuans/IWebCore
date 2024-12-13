#include "IMultiPart.h"
#include "core/util/IConstantUtil.h"
#include "http/biscuits/IHttpHeader.h"
#include "http/invalid/IHttpBadRequestInvalid.h"
#include "http/net/IRequest.h"

$PackageWebCoreBegin

const IMultiPart IMultiPart::Empty;
const static IStringView FORMDATE_NAME("name=");
const static IStringView FORMDATA_FILE_NAME("filename=");
const static IStringView FORMDATA_CHARSET("charset=");

namespace detail
{
    IStringViewList concatenateHeaders(const IStringViewList& list, IRequest* request);
    void resolveHeaders(IMultiPart* self, IStringView data, IRequest* request);
}

IMultiPart::IMultiPart(IStringView view, IRequest* request)
{
    auto index = view.find("\r\n\r\n");
    if(index == std::string_view::npos){
        request->setInvalid(IHttpBadRequestInvalid("multipart has no headers"));
        return;
    }

    m_content = view.substr(index+4);
    detail::resolveHeaders(this, view.substr(0, index), request);
}

IMultiPart::IMultiPart(IMultiPart &&value)
{
    this->operator =(std::move(value));
}

IMultiPart& IMultiPart::operator =(IMultiPart&& value)
{
    this->m_name = value.m_name;
    this->m_charset = value.m_charset;
    this->m_content = value.m_content;
    this->m_encoding = value.m_encoding;
    this->m_fileName = value.m_fileName;
    this->m_headers = value.m_headers;
    this->m_mime = value.m_mime;
    return *this;
}

bool IMultiPart::isValid() const
{
    return !m_content.empty() && !m_name.empty();
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

void detail::resolveHeaders(IMultiPart* self, IStringView data, IRequest* request)
{
    self->m_headers = detail::concatenateHeaders(data.split(IStringView("\r\n")), request);
    for(auto line : self->m_headers){
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
                self->m_name = value.substr(index+FORMDATE_NAME.length());
                if(!self->m_name.empty() && self->m_name.startWith("\"")){
                    self->m_name = self->m_name.substr(1);
                    index = self->m_name.find("\"");
                    self->m_name = self->m_name.substr(0, index);
                }
            }
            index = value.find(FORMDATA_FILE_NAME);
            if(index != std::string_view::npos){
                self->m_fileName = value.substr(index+FORMDATA_FILE_NAME.length());
                if(!self->m_fileName.empty() && self->m_fileName.startWith("\"")){
                    self->m_fileName = self->m_fileName.substr(1, self->m_fileName.length()-2);
                }
            }

        }else if(key == IHttpHeader::ContentType){
            self->m_mime = IHttpMimeUtil::toMime(value);
            auto index = value.find(FORMDATA_CHARSET);
            if(index != std::string_view::npos){
                IStringViewList args = value.substr(index+FORMDATA_CHARSET.length()).split(";");
                if(args.length() >= 1){
                    self->m_charset= args.first().trimmed();
                }
            }
        }else if(key ==  IHttpHeader::ContentTransferEncoding){
            if(value == "7bit"){
                self->m_encoding = IMultiPart::BIT_7;
            }else if(value == "8bit"){
                self->m_encoding = IMultiPart::BIT_8;
            }else if(value == "binary"){
                self->m_encoding = IMultiPart::BINARY;
            }else{
                request->setInvalid(IHttpBadRequestInvalid("multipart header error with ContentTransferEncoding"));
            }
        }
    }
}

$PackageWebCoreEnd
