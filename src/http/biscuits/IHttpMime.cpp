#include "IHttpMime.h"
#include "core/abort/IAbortInterface.h"

$PackageWebCoreBegin

class IHttpMimeAbort : IAbortInterface<IHttpMimeAbort>
{
    $AsAbort(
        http_mime_already_exist
    )
protected:
    virtual QMap<int, QString> abortDescription() const final {
        return {
            {http_mime_already_exist, "user register mime already exist, please duplicated this mime"}
        };
    }
};

namespace detail{
    const IStringList & getMimeStringList(){
        static const IStringList mimes = {
            // TEXT  16
            "text/plain",                                               // TEXT_PLAIN
            "text/plain; charset=UTF-8",                                // TEXT_PLAIN_UTF8
            "text/html",                                                // TEXT_HTML
            "text/html; charset=UTF-8",                                 // TEXT_HTML_UTF8
            "text/calendar",											//	TEXT_CALENDAR
            "text/css",                                                 // TEXT_CSS
            "text/directory",                                           // TEXT_DIRECTORY
            "text/enriched",                                            // TEXT_ENRICHED
            "text/parityfec",                                           // TEXT_PARITYFIC
            "text/richtext",                                           	// TEXT_RICHTEXT
            "text/rtf",                                                 // TEXT_RTF
            "text/sgml",                                                // TEXT_SGML
            "text/t140",                                                // TEXT_T140
            "text/uri-list",                                            // TEXT_URI_LIST
            "text/vnd.curl",                                            // TEXT_VND_CURL
            "text/xml",                                                 // TEXT_XML

            //IMAGE 12
            "image/vnd.microsoft.icon",                                 // IMAGE_MICROSOFT_ICO
            "image/jpeg",                                               // IMAGE_JPEG
            "image/png",                                                // IMAGE_PNG
            "image/tiff",                                               // IMAGE_TIFF
            "image/svg+xml",                                            // IMAGE_SVG_XML
            "image/bmp",                                                // IMAGE_BMP
            "image/cgm",                                                // IMAGE_CGM
            "image/g3fax",                                              // IMAGE_G3FAX
            "image/gif",                                                // IMAGE_GIF
            "image/ief",                                                // IMAGE_IEF
            "image/webp",                                               // IMAGE_WEBP
            "image/x-icon",                                             // IMAGE_X_ICON

            //AUDIO 19
            "audio/midi",                                               // AUDIO_MIDI
            "audio/mpeg",           // 编码 MP3， mp2, mpga              // AUDIO_MPEG
            "audio/x-wav",          // 编码 *.wav 文件                   // AUDIO_X_WAV
            "audio/a-aiff",          // 编码 aif aiff aifc               // AUDIO_X_AIFF
            "audio/webm",                                               // AUDIO_WEBM
            "audio/ogg",                                                // AUDIO_OGG
            "audio/wav",                                                // AUDIO_WAV
            "audio/3gpp",                                               // AUDIO_3GPP
            "audio/3gpp2",                                              // AUDIO_3GPP2
            "audio/aac",                                                // AUDIO_AAC
            "audio/ac3",                                                // AUDIO_AC3
            "audio/AMR",                                                // AUDIO_AMR
            "audio/AMR-WB",                                             // AUDIO_AMR_WB
            "audio/amr-wb+",                                            // AUDIO_AMR_WB_PLUS
            "audio/mp4",                                                // AUDIO_MP4
            "audio/mp3",                                                // AUDIO_MP3
            "audio/mp2",                                                // AUDIO_MP2
            "audio/basic",                                              // AUDIO_BASIC
            "audio/x-ms-wma",                                           // AUDIO_X_WMA

            //VIDEO 14
            "video/x-flv",                                              // VIDEO_FLV
            "video/mpeg",          // mpeg mpg                          // VIDEO_MPEG
            "video/parityfec",                                          // VIDEO_PARITYFEC
            "video/quicktime",     // mov                               // VIDEO_QUICKTIME
            "video/x-msvideo",     // AVI                               // VIDEO_X_MSVIDEO
            "video/mp4",           // mp4                               // VIDEO_MP4
            "video/x-flv",         // flv                               // VIDEO_X_FLV
            "video/ogg",                                                // VIDEO_OGG
            "video/webm",                                               // VIDEO_WEBM
            "video/3gpp",                                               // VIDEO_3GPP
            "video/3gpp2",                                              // VIDEO_3GPP2
            "video/raw",                                                // VIDEO_RAW
            "video/x-ms-wmv",                                           // VIDEO_X_WMV
            "video/x-m4v",                                              // VIDEO_X_M4V

            //APPLICATION  18
            "application/msword",                                       // APPLICATION_MSWORD
            "application/rtf",                                          // APPLICATION_RTF
            "application/vnd.ms-excel",                                 // APPLICATION_EXCEL
            "application/json",                                         // APPLICATION_JSON
            "application/json; charset=UTF-8",                          // APPLICATION_JSON_UTF8
            "application/vnd.ms-powerpoint",                            // APPLICATION_POWER_POINT
            "application/javascript",                                   // APPLICATION_JAVASCRIPT
            "application/vnd.oasis.opendocument.text",                  // APPLICATION_OPEN_DOCUMENT_TEXT
            "application/vnd.oasis.opendocument.spreadsheet",           // APPLICATION_OPEN_DOCUMENT_SPREADSHEET
            "application/x-shockwave-flash",                            // APPLICATION_SHOCKWAVE_FLASH
            "application/x-rar-compressed",                             // APPLICATION_RAR_COMPRESSED
            "application/x-msdownload",                                 // APPLICATION_MS_DOWNLOAD
            "application/vnd.ms-cab-compressed",                        // APPLICATION_CAB_COMPRESSED
            "application/postscript",                                   // APPLICATION_POSTSCRIPT
            "application/x-www-form-urlencoded",                        // APPLICATION_WWW_FORM_URLENCODED
            "application/x-font-woff",                                  // APPLICATION_FONT_WOFF
            "application/octet-stream",                                 // APPLICATION_FONT_TTF
            "application/octet-stream",                                 // APPLICATION_OCTET_STREAM
            "application/pdf",                                          // APPLICATION_PDF

            //MULTIPART 12
            "multipart/alternative",									// MULTIPART_ALTERNATIVE
            "multipart/form-data",										// MULTIPART_FORM_DATA
            "multipart/byteranges",										// MULTIPART_BYTERANGES
            "multipart/digest",											// MULTIPART_DIGEST
            "multipart/encrypted",								        // MULTIPART_ENCRYTED
            "multipart/header-set",                                     // MULTIPART_HEADER_SET
            "multipart/mixed",                                          // MULTIPART_MIXED
            "multipart/parallel",                                       // MULTIPART_PARALLEL
            "multipart/related",                                        // MULTIPART_RELATED
            "multipart/report",                                         // MULTIPART_REPORT
            "multipart/signed",                                         // MULTIPART_SIGNED
            "multipart/vocie-message",                                  // MULTIPART_VOICE_MESSAGE

            // UNKOWN
            "UNKNOWN"                                                   // UNKNOWN
        };
        return mimes;
    }

    const QMap<IString, IHttpMime>& getSystemSuffixMimeMap(){
        static const QMap<IString, IHttpMime> suffixMimePair = {
            // TEXT
            {"txt", IHttpMime::TEXT_PLAIN_UTF8},

            {"xhtml", IHttpMime::TEXT_HTML_UTF8},
            {"html", IHttpMime::TEXT_HTML_UTF8},
            {"htm", IHttpMime::TEXT_HTML_UTF8},

            {"css", IHttpMime::TEXT_CSS},

            {"xml", IHttpMime::TEXT_XML},
            {"xql", IHttpMime::TEXT_XML},
            {"xsd", IHttpMime::TEXT_XML},
            {"xslt", IHttpMime::TEXT_XML},
            {"cml", IHttpMime::TEXT_XML},
            {"dcd", IHttpMime::TEXT_XML},
            {"ent", IHttpMime::TEXT_XML},
            {"mtx", IHttpMime::TEXT_XML},
            {"rdf", IHttpMime::TEXT_XML},
            {"tsd", IHttpMime::TEXT_XML},
            {"wsdl", IHttpMime::TEXT_XML},
            //    {"xq", IHttpMime::TEXT_XML},
            //    {"xquery", IHttpMime::TEXT_XML},
            {"xsl", IHttpMime::TEXT_XML},
            {"biz", IHttpMime::TEXT_XML},
            //    {"svg", IHttpMime::TEXT_XML},
            {"vxml", IHttpMime::TEXT_XML},
            {"vml", IHttpMime::TEXT_XML},
            {"tld", IHttpMime::TEXT_XML},
            {"math", IHttpMime::TEXT_XML},

            // IMAGE
            {"png",  IHttpMime::IMAGE_PNG},
            {"jpg",  IHttpMime::IMAGE_JPEG},
            {"jpeg",  IHttpMime::IMAGE_JPEG},
            {"jpe",  IHttpMime::IMAGE_JPEG},
            {"jfif",  IHttpMime::IMAGE_JPEG},
            {"bmp",  IHttpMime::IMAGE_BMP},
            {"cgm",  IHttpMime::IMAGE_CGM},
            {"ief",  IHttpMime::IMAGE_IEF},
            {"tif",  IHttpMime::IMAGE_TIFF},
            {"tiff",  IHttpMime::IMAGE_TIFF},
            {"webp",  IHttpMime::IMAGE_WEBP},
            {"ico",  IHttpMime::IMAGE_X_ICON},
            {"svg",  IHttpMime::IMAGE_SVG_XML},
            {"gif",  IHttpMime::IMAGE_GIF},

            //AUDIO
            {"mpga", IHttpMime::AUDIO_MPEG},
            {"aac", IHttpMime::AUDIO_AAC},
            {"ac3", IHttpMime::AUDIO_AC3},
            {"amr", IHttpMime::AUDIO_AMR},
            {"ogg", IHttpMime::AUDIO_OGG},
            {"wav", IHttpMime::AUDIO_WAV},
            {"3gpp", IHttpMime::AUDIO_3GPP},
            {"rmi", IHttpMime::AUDIO_MIDI},
            {"mid", IHttpMime::AUDIO_MIDI},
            {"midi", IHttpMime::AUDIO_MIDI},
            {"webm", IHttpMime::AUDIO_WEBM},
            {"3gp2", IHttpMime::AUDIO_3GPP2},
            {"aif", IHttpMime::AUDIO_X_AIFF},
            {"aiff", IHttpMime::AUDIO_X_AIFF},
            {"aifc", IHttpMime::AUDIO_X_AIFF},
            {"mid", IHttpMime::AUDIO_MIDI},
            {"midi", IHttpMime::AUDIO_MIDI},

            {"au", IHttpMime::AUDIO_BASIC},
            {"snd", IHttpMime::AUDIO_BASIC},
            {"wax", IHttpMime::AUDIO_X_WAV},
            {"mp3", IHttpMime::AUDIO_MP3},
            {"mp2", IHttpMime::AUDIO_MP2},
            {"midi", IHttpMime::AUDIO_MIDI},
            {"wma", IHttpMime::AUDIO_X_WMA},

            // VIDEO
            {"flv", IHttpMime::VIDEO_FLV},
            {"mp4", IHttpMime::VIDEO_MP4},
            {"mpg", IHttpMime::VIDEO_MPEG},
            {"mp2v", IHttpMime::VIDEO_MPEG},
            {"mpeg", IHttpMime::VIDEO_MPEG},
            {"mps", IHttpMime::VIDEO_MPEG},
            {"avi", IHttpMime::VIDEO_X_MSVIDEO},
            {"3gp", IHttpMime::VIDEO_3GPP},
            {"m4v", IHttpMime::VIEDO_X_M4V},
            {"wmv", IHttpMime::VIDEO_X_WMV},
            {"webm", IHttpMime::VIDEO_WEBM},
            {"mov", IHttpMime::VIDEO_QUICKTIME},

            // APPLICATION
            {"json", IHttpMime::APPLICATION_JSON},
            {"js", IHttpMime::APPLICATION_JAVASCRIPT},
            {"bin", IHttpMime::APPLICATION_OCTET_STREAM},
            {"exe", IHttpMime::APPLICATION_OCTET_STREAM},
            {"pdf", IHttpMime::APPLICATION_PDF}
        };
        return suffixMimePair;
    }

    static std::map<IString, IString> m_userDefinedSuffixes;
}

const IString& IHttpMimeUtil::toString(IHttpMime mime)
{
    static const auto& mimes = detail::getMimeStringList();
    int mimeValue = static_cast<int>(mime);
    if(mimeValue < 0 || mimeValue >mimes.length()-1){
        return IHttpMimeUtil::MIME_UNKNOWN_STRING;
    }

    return mimes[static_cast<int>(mime)];
}

IHttpMime IHttpMimeUtil::toMime(const QString &string)
{
    return toMime(IString(string.toUtf8()));
}

IHttpMime IHttpMimeUtil::toMime(const IString& data)
{
    static const auto& mimes = detail::getMimeStringList();
    static IString splitter = ";";
    IString type = data.split(splitter).first();

    auto index = mimes.indexOf(type);
    if(index < 0 || index == mimes.length()-1){
        return  IHttpMime(index);
    }
    return IHttpMime::UNKNOWN;
}

// TODO: 这里没有做大小写匹配, 目的是为了性能，之后可以考虑做一下。
const IString& IHttpMimeUtil::getSuffixMime(const IString &suffix)
{
    if(suffix.isEmpty()){
        return IHttpMimeUtil::MIME_UNKNOWN_STRING;
    }

    static const IStringList keys = detail::getSystemSuffixMimeMap().keys();
    if(keys.contains(suffix)){
        return IHttpMimeUtil::toString(detail::getSystemSuffixMimeMap()[suffix]);
    }

    if(detail::m_userDefinedSuffixes.find(suffix) != detail::m_userDefinedSuffixes.end()){
        return detail::m_userDefinedSuffixes[suffix];
    }

    return IHttpMimeUtil::MIME_UNKNOWN_STRING;
}

void IHttpMimeUtil::registerSuffixMime(IString suffix, IString mime)
{
    suffix.solidify();
    mime.solidify();
    detail::m_userDefinedSuffixes[std::move(suffix)] = std::move(mime);
}

$PackageWebCoreEnd
