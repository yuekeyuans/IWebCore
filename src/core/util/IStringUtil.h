﻿#pragma once

// I NEED CPP20!!
#include "core/util/IHeaderUtil.h"

$PackageWebCoreBegin

namespace IStringUtil
{
    inline bool startsWith(const std::string& str, const std::string& prefix) {
        return str.compare(0, prefix.size(), prefix) == 0;
    }
//    inline bool startWith(const std::string& str, char); // and so on

    inline bool endsWith(const std::string& str, const std::string& suffix) {
        if (str.size() < suffix.size()) return false;
        return str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
    }

    // `mid` 方法，默认 length 为 -1（表示从 start 到结尾）
    inline std::string mid(const std::string& str, size_t start, int length = -1) {
        if (start >= str.size()) {
            return "";  // 如果起始位置超出范围，返回空字符串
        }

        // 如果 length 是 -1，则获取从 start 到结尾的子字符串
        if (length == -1) {
            length = str.size() - start;
        }

        return str.substr(start, length);  // 获取从 start 开始的 length 长度的子字符串
    }

    // `left` 方法，默认 length 为 -1（表示获取整个字符串）
    inline std::string left(const std::string& str, int length = -1) {
        if (length == -1 || length >= str.size()) {
            return str;  // 如果 length 是 -1 或者大于等于字符串长度，返回整个字符串
        }
        return str.substr(0, length);  // 获取从开头开始的 length 长度的子字符串
    }

    // `right` 方法，默认 length 为 -1（表示获取整个字符串）
    inline std::string right(const std::string& str, int length = -1) {
        if (length == -1 || length >= str.size()) {
            return str;  // 如果 length 是 -1 或者大于等于字符串长度，返回整个字符串
        }
        return str.substr(str.size() - length, length);  // 获取从末尾开始的 length 长度的子字符串
    }
}

$PackageWebCoreEnd