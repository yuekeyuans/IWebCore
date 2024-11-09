#pragma once

#include "core/util/IHeaderUtil.h"

$PackageWebCoreBegin

struct IHttpUrlFragment
{
public:
    using ValidateFun = std::function<bool(const QString&)>;
    enum NodeType{
        TEXT_MATCH,     // match text
        REGEXP_MATCH,   // match reg
        FUNC_MATCH,     // match function
        FULL_MATCH      // empty node match, match any thing
    };

public:
    bool isMatch(IStringView);
    bool isMatch(const QString&);

public:
    QString fragment;
    NodeType type;
    QString name;
    QRegularExpression regexpValidator;     // 使用 正则式验证数据的正确性与否
    ValidateFun funValidator;               // 使用 函数 验证数据是否正确
};

$PackageWebCoreEnd
