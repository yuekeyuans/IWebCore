#pragma once

// I NEED CPP20!!
#include "core/util/IHeaderUtil.h"

$PackageWebCoreBegin

namespace IStringUtil
{
    inline bool startsWith(const std::string& str, const std::string& prefix) {
        return str.compare(0, prefix.size(), prefix) == 0;
    }

    inline bool endsWith(const std::string& str, const std::string& suffix) {
        if (str.size() < suffix.size()) return false;
        return str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
    }

    inline std::string mid(const std::string& str, size_t start, int length = -1) {
        if (start >= str.size()) {
            return "";  // 如果起始位置超出范围，返回空字符串
        }
        if (length == -1) {
            length = str.size() - start;
        }
        return str.substr(start, length);  // 获取从 start 开始的 length 长度的子字符串
    }

    inline std::string left(const std::string& str, std::size_t length = -1) {
        if (length == -1 || length >= str.size()) {
            return str;  // 如果 length 是 -1 或者大于等于字符串长度，返回整个字符串
        }
        return str.substr(0, length);  // 获取从开头开始的 length 长度的子字符串
    }

    inline std::string right(const std::string& str, std::size_t length = -1) {
        if (length == -1 || length >= str.size()) {
            return str;  // 如果 length 是 -1 或者大于等于字符串长度，返回整个字符串
        }
        return str.substr(str.size() - length, length);  // 获取从末尾开始的 length 长度的子字符串
    }

    inline void print(const IString& data){
        qDebug() << data.m_view.toQString();
    }

    inline void print(const asio::const_buffer& data){
        qDebug() << "CONST BUFFER:"
                 << QString::number(data.size())
                 << IString(IStringView(reinterpret_cast<const char*>(data.data()), data.size())).m_view.toQString();
    }
}

$PackageWebCoreEnd
