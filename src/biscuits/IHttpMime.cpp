#include "IHttpMime.h"

$PackageWebCoreBegin

QString IHttpMimeHelper::toString(IHttpMime mime)
{
    if(mime == IHttpMime::UNKNOWN){
        return "UNKNOWN";
    }
    return getMimeList()[static_cast<int>(mime)];
}

IHttpMime IHttpMimeHelper::toMime(const QString &string)
{
    static int lastLength = getMimeList().length() -1;
    auto type = string.split(";").first().toLower().trimmed();
    auto index = getMimeList().indexOf(type);
    if(index == -1 || index == lastLength){
        return IHttpMime::UNKNOWN;
    }
    return static_cast<IHttpMime>(index);
}

const QStringList &IHttpMimeHelper::getMimeList(){
    const static QStringList mimes = {
        // TEXT  15
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

        //AUDIO 15
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

        //VIDEO 12
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

        //APPLICATION  17
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

        "UNKNOWN",                                                  // UNKNOWN
    };
    return mimes;
}

const QStringList &IHttpMimeHelper::getMimeSuffixes()
{
    const static QStringList mimeSuffixes = {
        // TODO: may be unused
    };
    return mimeSuffixes;
}


$PackageWebCoreEnd
