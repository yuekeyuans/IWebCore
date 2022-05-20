#pragma once

#include "base/IHeaderUtil.h"
#include "base/IPreProcessorUtil.h"
#include "base/IMetaUtil.h"
#include "web/biscuits/IHttpMime.h"
#include "core/bean/IBeanPreProcessor.h"
#include "core/unit/IRegisterMetaTypeUnit.h"

$PackageWebCoreBegin

class IMultiPart : public IRegisterMetaTypeUnit<IMultiPart>
{
    Q_GADGET
    $UseMetaRegistration(IMultiPart);
public:
    enum TransferEncoding{      // rfc2046
        BIT_7,                  // ascii
        BIT_8,                  // 不止 ascii, 但仍然包含字符
        BINARY,                 // binary data
    };

public:
    IMultiPart();
    void resolveHeaders();

public:
    QMap<QString, QString> headers;
    QVector<IMultiPart> parts;
    QString name;
    QString fileName;
    QString charset;
    QByteArray content;
    IHttpMime mime {IHttpMime::UNKNOWN};
    TransferEncoding encoding{BIT_7};
};

$PackageWebCoreEnd
