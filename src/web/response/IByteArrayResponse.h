#pragma once
#include "IResponseInterface.h"
#include "IResponsePreProcessor.h"

$PackageWebCoreBegin

class IByteArrayResponse : public IResponseInterface<IByteArrayResponse>
{
    $AsResponse(IByteArrayResponse)
public:
    using IResponseInterface::operator[];
    using IResponseInterface::IResponseInterface;

public:
    IByteArrayResponse();
    IByteArrayResponse(const char*);
    IByteArrayResponse(QByteArray &array);  // TODO: 这个函数可能有些问题，不能够大规模使用
    IByteArrayResponse(QByteArray &&array);

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
