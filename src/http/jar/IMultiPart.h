#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/base/IMetaUtil.h"
#include "core/base/IPreProcessorUtil.h"
#include "core/unit/IRegisterMetaTypeUnit.h"
#include "http/biscuits/IHttpMime.h"

$PackageWebCoreBegin

class IMultiPartJar;
class IMultiPart : IRegisterMetaTypeUnit<IMultiPart>
{
public:
    enum TransferEncoding{      // rfc2046
        BIT_7,                  // ascii
        BIT_8,                  // 不止 ascii, 但仍然包含字符
        BINARY,                 // binary data
    };

public:
    IMultiPart();
    IMultiPart(IStringView);

    bool isValid() const;

private:
    void resolveHeaders(IStringView);

public:
    IStringView name;
    IStringView fileName;
    IStringView charset;
    IStringView content;
    IHttpMime mime {IHttpMime::UNKNOWN};
    TransferEncoding encoding{BIT_7};
    QMultiHash<IStringView, IStringView> headers; // TODO: 这个能不能变成可拷贝的一个内容？

private:
    friend class IMultiPartJar;
};

$PackageWebCoreEnd
