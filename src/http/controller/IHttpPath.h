#pragma once

#include "core/util/IHeaderUtil.h"

$PackageWebCoreBegin

struct IHttpPathFragment
{
public:
    using Validator = std::function<bool(const QString&)>;
    enum PathType{
        TEXT,     // match text
        FUNCTION,     // match function
        FULL_MATCH      // empty node match, match any thing
    };

public:
    bool isMatch(IStringView) const;
    bool isMatch(const QString&) const;

public:
    PathType m_type{PathType::FULL_MATCH};
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
