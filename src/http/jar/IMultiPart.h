#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/base/IMetaUtil.h"
#include "core/base/IPreProcessorUtil.h"
#include "core/unit/IRegisterMetaTypeUnit.h"
#include "http/biscuits/IHttpMime.h"

$PackageWebCoreBegin

class IMultiPartJar;
class IRequest;
class IMultiPart : IRegisterMetaTypeUnit<IMultiPart>
{
    friend class IMultiPartJar;
public:
    enum TransferEncoding{      // rfc2046
        BIT_7,
        BIT_8,
        BINARY,
    };

public:
    IMultiPart() = default;
    IMultiPart(IStringView data, IRequest* request);

public:
    bool isValid() const;

public:
    IStringView name;
    IStringView fileName;
    IStringView charset;
    IStringView content;
    IHttpMime mime {IHttpMime::UNKNOWN};
    TransferEncoding encoding{BIT_7};
    IStringViewList headers; // TODO: 这个能不能变成可拷贝的一个内容？
};

$PackageWebCoreEnd
