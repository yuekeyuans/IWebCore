#include "IHttpStatus.h"

$PackageWebCoreBegin

QString IHttpStatusUtil::toString(const IHttpStatus statusCode)
{
    return QString::number(static_cast<int>(statusCode));
}

QString IHttpStatusUtil::toStringDescription(IHttpStatus statusCode)
{
    const auto& description = getStatusDescription();
    if(!description.contains(static_cast<int>(statusCode))){
        return "unknown";
    }
    return getStatusDescription()[static_cast<int>(statusCode)];
}

IHttpStatus IHttpStatusUtil::toStatus(int statusCode)
{
    const auto& description = getStatusDescription();
    if(!description.contains(statusCode)){
        return IHttpStatus::UNKNOWN;
    }
    return IHttpStatus(statusCode);
}

IHttpStatus IHttpStatusUtil::toStatus(const QString &statusCode)
{
    auto code = statusCode.toInt();
    return toStatus(code);
}

const QMap<int, QString> &IHttpStatusUtil::getStatusDescription()
{
    const static QMap<int, QString> descriptionTable = {
        // 1XX
        {100, "Continue"},
        {101, "Switching Protocols"},
        {102, "Processing"},
        {103, "Early Hints"},

        // 2XX
        {200, "OK"},
        {201, "Created"},
        {202, "Accepted"},
        {203, "Non-Authoritative Information"},
        {204, "No Content"},
        {205, "Reset Content"},
        {206, "Partial Content"},
        {207, "Multi-Status"},
        {208, "Already Reported"},
        {226, "IM Used"},

        // 3XX
        {300, "Multiple Choice"},
        {301, "Moved Permanently"},
        {302, "Found"},
        {303, "See Other"},
        {304, "Not Modified"},
        {305, "Use Proxy"},
        {306, "unused"},
        {307, "Temporary Redirect"},
        {308, "Permanent Redirect"},

        // 4XX
        {400, "Bad Request"},
        {401, "Unauthorized"},
        {402, "Payment Required"},
        {403, "Forbidden"},
        {404, "Not Found"},
        {405, "Method Not Allowed"},
        {406, "Not Acceptable"},
        {407, "Proxy Authentication Required"},
        {408, "Request Timeout"},
        {409, "Conflict"},
        {410, "Gone"},
        {411, "Length Required"},
        {412, "Precondition Failed"},
        {413, "Payload Too Large"},
        {414, "URI Too Long"},
        {415, "Unsupported Media Type"},
        {416, "Range Not Satisfiable"},
        {417, "Expectation Failed"},
        {418, "I'm a teapot"},
        {421, "Misdirected Request"},
        {422, "Unprocessable Entity"},
        {423, "Locked"},
        {424, "Failed Dependency"},
        {425, "Too Early"},
        {426, "Upgrade Required"},
        {428, "Precondition Required"},
        {429, "Too Many Requests"},
        {431, "Request Header Fields Too Large"},
        {451, "Unavailable For Legal Reasons"},

        // 5XX
        {500, "Internal Server Error"},
        {501, "Not Implemented"},
        {502, "Bad Gateway"},
        {503, "Service Unavailable"},
        {504, "Gateway Timeout"},
        {505, "HTTP Version Not Supported"},
        {506, "Variant Also Negotiates"},
        {507, "Insufficient Storage"},
        {508, "Loop Detected"},
        {510, "Not Extended"},
        {511, "Network Authentication Required"},

        // other
        {1024, "UNKNOWN"}
    };
    return descriptionTable;
}


$PackageWebCoreEnd
