#pragma once

#include "core/util/IHeaderUtil.h"

struct IHttpRouteNote
{
    using ValidateFun = std::function<bool(const QString&)>;

    enum NodeType{
        TEXT_MATCH,
        REGEXP_MATCH,
        FUNC_MATCH,
        FULL_MATCH
    };

    NodeType type;
    QString name;
    QString fragment;
    QRegularExpression regexpValidator;     // 使用 正则式验证数据的正确性与否
    ValidateFun funValidator;               // 使用 函数 验证数据是否正确
};
