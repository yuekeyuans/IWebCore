#pragma once

#include "core/util/IHeaderUtil.h"

$PackageWebCoreBegin

struct IHttpUrlFragment
{
public:
    using ValidateFun = std::function<bool(const QString&)>;
    enum NodeType{
        TEXT_MATCH,
        REGEXP_MATCH,
        FUNC_MATCH,
        FULL_MATCH
    };

public:
    QString fragment;
    NodeType type;
    QString name;
    QRegularExpression regexpValidator;     // 使用 正则式验证数据的正确性与否
    ValidateFun funValidator;               // 使用 函数 验证数据是否正确
};

$PackageWebCoreEnd
