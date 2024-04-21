#pragma once

#include <QtCore>
#include "http/response/IResponseTemplateRenderer.h"
#include "core/config/IProfileImport.h"

namespace IWebCore {

struct INody;
class INodyRenderer : public IResponseTemplateRenderer
{
public:
    INodyRenderer();
    ~INodyRenderer();

public:
    virtual bool isPathExist(const QString &path) final;
    virtual QString render(const QString &path, const QJsonObject &object) final;
    virtual QString getPage(IHttpStatus) final;
    virtual QString getPage(PageType) final;

    void addNody(const QString& path, INody* nody);

private:
    QHash<QString, INody*> m_nodyHash;
    $QString m_defaultPrefix{"http.templates.nody.defaultNodyTemplatePrefix"};
    $QString m_userDefinedPrefix{"http.templates.nody.userDefinedNodyTemplatePrefix"};
};

}
