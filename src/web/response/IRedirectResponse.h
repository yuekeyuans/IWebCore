#pragma once

#include "IResponseInterface.h"
#include "IResponsePreProcessor.h"
#include "web/biscuits/IHttpStatus.h"

$PackageWebCoreBegin

class IRedirectResponse : public IResponseInterface<IRedirectResponse>
{
    $AsResponse(IRedirectResponse)
public:
    using IResponseInterface::operator[];
    using IResponseInterface::IResponseInterface;

public:
    IRedirectResponse();
    virtual ~IRedirectResponse() = default;

    IRedirectResponse(const char *path);
    IRedirectResponse(const QString &path);

    IRedirectResponse& addAttribute(QString key, QString value);
    IRedirectResponse& addAttribute(QMap<QString, QString> attribute);
    IRedirectResponse& setRedirectPath(const QString& path);

//    virtual void parsePrefixCommand(QString &&data) final;
    virtual void setInstanceCopy(IResponseWare *) final;
//    virtual bool canConvertFromString() final;
//    virtual bool matchConvertString(const QString &data) final;
    virtual QString getPrefixMatcher() final;


public:
    void updateLocationPath();

private:
    QString redirectPath;
    QMap<QString, QString> attributes;
};

IRedirectResponse operator"" _redirect(const char* str, size_t size);

$PackageWebCoreEnd

