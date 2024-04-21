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

    void resolveHeaders();
    bool isValid() const;

public:
    QMap<QString, QString> headers;
    QVector<IMultiPart> parts;
    QString name;
    QString fileName;
    QString charset;
    QByteArray content;
    IHttpMime mime {IHttpMime::UNKNOWN};
    TransferEncoding encoding{BIT_7};

private:
    static const IMultiPart InvalidMulitPart;
    friend class IMultiPartJar;
};

$PackageWebCoreEnd
