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
    NodeType m_type{NodeType::FULL_MATCH};
    QString m_fragment;
    QString m_name;
    Validator m_validator{nullptr};
};

struct IHttpPath
{
public:
    QString m_path;
    std::vector<IHttpPathFragment> m_fragments;
};

$PackageWebCoreEnd
