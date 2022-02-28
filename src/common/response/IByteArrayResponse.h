#pragma once
#include "IResponseInterface.h"
#include "IResponsePreProcessor.h"
#include "IRedirectResponse.h"

$PackageWebCoreBegin

class IByteArrayResponse : public IResponseInterface<IByteArrayResponse>
{
    Q_GADGET
    $AsResponse(IByteArrayResponse)
public:
    using IResponseInterface::operator[];

public:
    IByteArrayResponse();
    IByteArrayResponse(QByteArray &array);  // TODO: 这个函数可能有些问题，不能够大规模使用
    IByteArrayResponse(QByteArray &&array);
    IByteArrayResponse(IRedirectResponse&& redirectResponse);

    virtual void setInstanceArg(QString &&value) final;
    virtual void setInstanceArg(void *arg, const QString &tag = "") final;
    virtual bool canConvertFromString() final;
    virtual bool matchConvertString(const QString &value) final;

    static QSharedPointer<IResponseWare> createByteArrayInstance();
    virtual QSharedPointer<IResponseWare> createInstance() final;

private:
    static const QString m_matcherPrefix;
};

IByteArrayResponse operator"" _bytes(const char* str, size_t size);

$PackageWebCoreEnd
