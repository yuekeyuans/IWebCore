#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/util/IMetaUtil.h"
#include "core/util/IPreProcessorUtil.h"
#include "core/unit/IRegisterMetaTypeUnit.h"
#include "http/biscuits/IHttpMime.h"

$PackageWebCoreBegin

class IMultiPartJar;
class IRequest;
class IMultiPart
{
public:
    enum TransferEncoding{      // rfc2046
        BIT_7,
        BIT_8,
        BINARY,
    };

public:
    IMultiPart() = default;
    IMultiPart(IStringView data, IRequest* request);
    IMultiPart(const IMultiPart&) = delete;
    IMultiPart& operator = (const IMultiPart&) = delete;
    IMultiPart(IMultiPart&&);
    IMultiPart& operator = (IMultiPart&&);

public:
    bool isValid() const;

public:
    IStringView m_name;
    IStringView m_fileName;
    IStringView m_charset;
    IStringView m_content;
    IHttpMime m_mime {IHttpMime::UNKNOWN};
    TransferEncoding m_encoding{BIT_7};
    IStringViewList m_headers;

public:
    static const IMultiPart Empty;
};

$PackageWebCoreEnd
