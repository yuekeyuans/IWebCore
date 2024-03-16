#pragma once
#include "IResponseInterface.h"
#include "IResponsePreProcessor.h"

$PackageWebCoreBegin

class IByteArrayResponse : public IResponseInterface<IByteArrayResponse>
{
public:
    IByteArrayResponse(const IByteArrayResponse &rhs) : IResponseInterface(rhs){
//        auto raw = new IResponseWareRaw(*rhs.raw);
//        delete this->raw;
//        this->raw = raw;
    }
    IByteArrayResponse& operator=(IByteArrayResponse &rhs){
        auto raw = new IResponseWareRaw(*rhs.raw);
        delete this->raw;
        this->raw = raw;
        return *this;
    }
    IByteArrayResponse& operator=(IByteArrayResponse &&rhs){
        std::swap(this->raw, rhs.raw);
        return *this;
    }
    IByteArrayResponse(IByteArrayResponse&& rhs) : IResponseInterface(std::forward<IByteArrayResponse>(rhs)){
//        std::swap(this->raw, rhs.raw);
    }

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
