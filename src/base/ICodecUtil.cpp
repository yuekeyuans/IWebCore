#include "ICodecUtil.h"

$PackageWebCoreBegin

QByteArray ICodecUtil::toBase64(const QString &content)
{
    return toBase64(content.toUtf8());
}

QByteArray ICodecUtil::toBase64(const QByteArray& content)
{
    return content.toBase64();
}

QByteArray ICodecUtil::toBase64(const char *content)
{
    return toBase64(QByteArray(content));
}

QByteArray ICodecUtil::fromBase64(const QString &content)
{
    return fromBase64(content.toUtf8());
}

QByteArray ICodecUtil::fromBase64(const QByteArray &content)
{
    return QByteArray::fromBase64(content);
}

QByteArray ICodecUtil::fromBase64(const char *content)
{
    return fromBase64(QByteArray(content));
}

quint16 ICodecUtil::crc16(const QString &content)
{
    auto data = content.toStdString();
    return qChecksum(data.c_str(), data.length());
}

QByteArray ICodecUtil::compress(const QString &content, int level)
{
    return qCompress(content.toUtf8(), level);
}

QByteArray ICodecUtil::compress(const QByteArray &content, int level)
{
    return qCompress(content, level);
}

QByteArray ICodecUtil::compress(const char *content, int level)
{
    return qCompress(content, level);
}

QByteArray ICodecUtil::uncompress(const QString &content)
{
    return uncompress(content.toUtf8());
}

QByteArray ICodecUtil::uncompress(const QByteArray &content)
{
    return qUncompress(content);
}

QByteArray ICodecUtil::uncompress(const char *content)
{
    return uncompress(QByteArray(content));
}

unsigned char ToHex(unsigned char x)
{
    return  x > 9 ? x + 55 : x + 48;
}

unsigned char FromHex(unsigned char x)
{
    unsigned char y{0};
    if (x >= 'A' && x <= 'Z') y = x - 'A' + 10;
    else if (x >= 'a' && x <= 'z') y = x - 'a' + 10;
    else if (x >= '0' && x <= '9') y = x - '0';
    else assert(0);
    return y;
}

QByteArray ICodecUtil::urlEncode(const QString &rawUrl)
{
    QByteArray str = rawUrl.toUtf8();
    return urlEncode(str);
}

QByteArray ICodecUtil::urlEncode(const QByteArray &str)
{
    QByteArray strTemp;
    uint length = str.length();
    for (uint i = 0; i < length; i++)
    {
        if (isalnum((unsigned char)str[i]) ||
            (str[i] == '-') ||
            (str[i] == '_') ||
            (str[i] == '.') ||
            (str[i] == '~'))
            strTemp += str[i];
        else if (str[i] == ' ')
            strTemp += "+";
        else
        {
            strTemp += '%';
            strTemp += ToHex((unsigned char)str[i] >> 4);
            strTemp += ToHex((unsigned char)str[i] % 16);
        }
    }
    return strTemp;
}

QByteArray ICodecUtil::urlDecode(const QString &rawUrl)
{
    QByteArray str = rawUrl.toLocal8Bit();
    return urlDecode(str);
}

QByteArray ICodecUtil::urlDecode(const QByteArray &str)
{
    QByteArray strTemp;
    uint length = str.length();
    for (uint i = 0; i < length; i++)
    {
        if (str[i] == '+') strTemp += ' ';
        else if (str[i] == '%')
        {
            assert(i + 2 < length);
            unsigned char high = FromHex((unsigned char)str[++i]);
            unsigned char low = FromHex((unsigned char)str[++i]);
            strTemp += high*16 + low;
        }
        else strTemp += str[i];
    }
    return strTemp;
}

QString ICodecUtil::pathEncode(const QString &rawPath)
{
    QByteArray strTemp;
    QByteArray str = rawPath.toLocal8Bit();

    uint length = str.length();
    for (uint i = 0; i < length; i++)
    {
        if (isalnum((unsigned char)str[i]) ||
            (str[i] == '-') ||
            (str[i] == '_') ||
            (str[i] == '.') ||
            (str[i] == '~') ||
            (str[i] == '/') ||
            (str[i] == ':'))
            strTemp += str[i];
        else if (str[i] == ' ')
            strTemp += "+";
        else
        {
            strTemp += '%';
            strTemp += ToHex((unsigned char)str[i] >> 4);
            strTemp += ToHex((unsigned char)str[i] % 16);
        }
    }
    return strTemp;
}

$PackageWebCoreEnd
