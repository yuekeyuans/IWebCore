#include "IMultiPart.h"
#include "http/biscuits/IHttpHeader.h"

$PackageWebCoreBegin

IMultiPart::IMultiPart(IStringView view)
{
    auto index = view.find("\r\n\r\n");
    if(index == std::string_view::npos){
        return;
    }
    resolveHeaders(view.substr(0, index));
    content = view.substr(index+4);
}

void IMultiPart::resolveHeaders(IStringView data)
{
    auto lines = data.split(IStringView("\r\n"));
    for(auto line : lines){
        auto index = line.find_first_of(':');
        if(index == std::string_view::npos){
            name = {};  // this will cause invalid
            return;
        }
        IStringView key = line.substr(0, index).trimmed();
        IStringView value = line.substr(index+1).trimmed();
        qDebug() << key << value;

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
}

bool IMultiPart::isValid() const
{
    return !content.empty() && !name.empty();
}

$PackageWebCoreEnd
