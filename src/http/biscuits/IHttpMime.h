#pragma once

#include "core/util/IHeaderUtil.h"

$PackageWebCoreBegin

enum class IHttpMime{
    //TEXT  16
    TEXT_PLAIN      			= 0			, // "text/plain";
    TEXT_PLAIN_UTF8							, // "text/plain; charset=UTF-8";
    TEXT_HTML                               , // "text/html";
    TEXT_HTML_UTF8							, // "text/html; charset=UTF-8";
    TEXT_CALENDAR                           , // "text/calendar"
    TEXT_CSS                                , // "text/css"
    TEXT_DIRECTORY                          , // "text/directory"
    TEXT_ENRICHED                           , // "text/enriched"
    TEXT_PARITYFIC                          , // "text/parityfec"
    TEXT_RICHTEXT                           , // "text/richtext"
    TEXT_RTF                                , // "text/rtf"
    TEXT_SGML                               , // "text/sgml"
    TEXT_T140                               , // "text/t140"
    TEXT_URI_LIST                           , // "text/uri-list"
    TEXT_VND_CURL                           , // "text/vnd.curl"
    TEXT_XML                                , // "text/xml"

    //IMAGE 12
    IMAGE_MICROSOFT_ICO    					, // "image/vnd.microsoft.icon";
    IMAGE_JPEG             					, // "image/jpeg";
    IMAGE_PNG                               , // "image/png"
    IMAGE_TIFF             					, // "image/tiff";
    IMAGE_SVG_XML          					, // "image/svg+xml";
    IMAGE_BMP                               , // "image/bmp",
    IMAGE_CGM                               , // "image/cgm",
    IMAGE_G3FAX                             , // "image/g3fax",
    IMAGE_GIF                               , // "image/gif",
    IMAGE_IEF                               , // "image/ief",
    IMAGE_WEBP                              , // "image/webp",
    IMAGE_X_ICON                            , // "image/x-icon",

    //AUDIO 19
    AUDIO_MIDI                              , // "audio/midi",
    AUDIO_MPEG                              , // "audio/mpeg",           // 编码 MP3， mp2, mpga
    AUDIO_X_WAV                             , // "audio/x-wav",          // 编码 *.wav 文件
    AUDIO_X_AIFF                            , // "audio/a-aiff"          // 编码 aif aiff aifc
    AUDIO_WEBM                              , // "audio/webm",
    AUDIO_OGG                               , // "audio/ogg"
    AUDIO_WAV                               , // "audio/wav"
    AUDIO_3GPP                              , // "audio/3gpp",
    AUDIO_3GPP2                             , // "audio/3gpp2",
    AUDIO_AAC                               , // "audio/aac",
    AUDIO_AC3                               , // "audio/ac3",
    AUDIO_AMR                               , // "audio/AMR",
    AUDIO_AMR_WB                            , // "audio/AMR-WB",
    AUDIO_AMR_WB_PLUS                       , // "audio/amr-wb+",
    AUDIO_MP4                               , // "audio/mp4",
    AUDIO_MP3                               , // "audio/mp3",
    AUDIO_MP2                               , // "audio/mp2",
    AUDIO_BASIC                             , // "audio/basic",
    AUDIO_X_WMA                             , // "audio/x-ms-wma"        // 编码 wma 文件

    //VIDEO 14
    VIDEO_FLV              					, // "video/x-flv";
    VIDEO_MPEG                              , // "video/mpeg",          // mpeg mpg
    VIDEO_PARITYFEC                         , // "video/parityfec",
    VIDEO_QUICKTIME                         , // "video/quicktime",     // mov
    VIDEO_X_MSVIDEO                         , // "video/x-msvideo",     // AVI
    VIDEO_MP4                               , // "video/mp4",           // mp4
    VIDEO_X_FLV                             , // "video/x-flv",         // flv
    VIDEO_OGG                               , // "video/ogg",
    VIDEO_WEBM                              , // "video/webm",
    VIDEO_3GPP                              , // "video/3gpp",
    VIDEO_3GPP2                             , // "video/3gpp2",
    VIDEO_RAW                               , // "video/raw",
    VIDEO_X_WMV                             , // "video/x-ms-wmv",
    VIEDO_X_M4V                             , // "video/x-m4v",

    //APPLICATION  18
    APPLICATION_MSWORD                      , // "application/msword";
    APPLICATION_RTF                         , // "application/rtf";
    APPLICATION_EXCEL                       , // "application/vnd.ms-excel";
    APPLICATION_JSON                        , // "application/json";
    APPLICATION_JSON_UTF8                   , // "application/json; charset=UTF-8";
    APPLICATION_POWER_POINT                 , // "application/vnd.ms-powerpoint";
    APPLICATION_JAVASCRIPT                  , // "application/javascript";
    APPLICATION_OPEN_DOCUMENT_TEXT          , // "application/vnd.oasis.opendocument.text";
    APPLICATION_OPEN_DOCUMENT_SPREADSHEET   , // "application/vnd.oasis.opendocument.spreadsheet";
    APPLICATION_SHOCKWAVE_FLASH             , // "application/x-shockwave-flash";
    APPLICATION_RAR_COMPRESSED              , // "application/x-rar-compressed";
    APPLICATION_MS_DOWNLOAD                 , // "application/x-msdownload";
    APPLICATION_CAB_COMPRESSED              , // "application/vnd.ms-cab-compressed";
    APPLICATION_POSTSCRIPT                  , // "application/postscript";
    APPLICATION_WWW_FORM_URLENCODED         , // "application/x-www-form-urlencoded";
    APPLICATION_FONT_WOFF                   , // "application/x-font-woff";
    APPLICATION_FONT_TTF                    , // "application/octet-stream";
    APPLICATION_OCTET_STREAM                , // "application/octet-stream";
    APPLICATION_PDF                         , // "application/pdf"

    //multipart 12
    MULTIPART_ALTERNATIVE                   , // multipart/alternative;
    MULTIPART_FORM_DATA                     , // multipart/form-data;
    MULTIPART_BYTERANGES                    , // multipart/byteranges;
    MULTIPART_DIGEST                        , // multipart/digest;
    MULTIPART_ENCRYTED                      , // multipart/encrypted;
    MULTIPART_HEADER_SET                    , // multipart/header-set;
    MULTIPART_MIXED                         , // multipart/mixed;
    MULTIPART_PARALLEL                      , // multipart/parallel;
    MULTIPART_RELATED                       , // multipart/related;
    MULTIPART_REPORT                        , // multipart/report;
    MULTIPART_SIGNED                        , // multipart/signed;
    MULTIPART_VOICE_MESSAGE                 , // multipart/vocie-message;

    //UNKNOWN
    UNKNOWN = 1024,
};

namespace IHttpMimeUtil
{
    inline static const IString MIME_UNKNOWN_STRING = "UNKNOWN";

    const IString& toString(IHttpMime);
    IHttpMime toMime(const QString &);
    IHttpMime toMime(const IString&);

    // TODO:
//    std::string getSuffixMime(const QString& suffix);
//    void registerSuffixMime(const QString& suffix, const std::string& mime);
//    void registerSuffixMime(const QMap<QString, QString>& map);
}

$PackageWebCoreEnd
