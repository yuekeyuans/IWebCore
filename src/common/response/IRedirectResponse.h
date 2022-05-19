#pragma once

#include "IResponseInterface.h"
#include "IResponsePreProcessor.h"
#include "common/biscuits/IHttpStatus.h"

$PackageWebCoreBegin

/**
 * @brief The IRedirectResponse to redirect url
 * @see https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers/Location
 */
class IRedirectResponse : public IResponseInterface<IRedirectResponse>
{
    Q_GADGET
    $AsResponse(IRedirectResponse)
public:
    using IResponseInterface::operator[];

public:
    IRedirectResponse();
    virtual ~IRedirectResponse() = default;

    IRedirectResponse(const char *path);
    IRedirectResponse(const QString &path);

    IRedirectResponse& addAttribute(QString key, QString value);
    IRedirectResponse& addAttribute(QMap<QString, QString> attribute);
    IRedirectResponse& setRedirectPath(const QString& path);

    virtual void setInstanceArg(QString &&data) final;
    virtual void setInstanceCopy(IResponseWare *) final;
    virtual bool canConvertFromString() final;
    virtual bool matchConvertString(const QString &data) final;

    virtual QSharedPointer<IResponseWare> createInstance() final;

public:
    void updateLocationPath();

private:
    static const QString m_matcherPrefix;
    QString redirectPath;
    QMap<QString, QString> attributes;
};

IRedirectResponse operator"" _redirect(const char* str, size_t size);

$PackageWebCoreEnd

