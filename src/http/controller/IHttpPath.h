#pragma once

#include "core/util/IHeaderUtil.h"

$PackageWebCoreBegin

struct IHttpPathFragment
{
public:
    using Validator = std::function<bool(const QString&)>;
    enum NodeType{
        TEXT_MATCH,     // match text
        FUNC_MATCH,     // match function
        FULL_MATCH      // empty node match, match any thing
    };

public:
    bool isMatch(IStringView) const;
    bool isMatch(const QString&) const;

public:
    QString m_fragment;
    NodeType m_type;
    QString m_name;
    Validator m_validator;               // 使用 函数 验证数据是否正确
};

struct IHttpPath
{
public:
    QString m_path;
    std::vector<IHttpPathFragment> m_fragments;
};

$PackageWebCoreEnd
