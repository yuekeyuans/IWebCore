#include "INodyRenderer.h"
#include "INody.h"

namespace IWebCore {

INodyRenderer::INodyRenderer()
{

}

INodyRenderer::~INodyRenderer()
{
    for(auto node : m_nodyHash){
        delete node;
    }
}

bool INodyRenderer::isPathExist(const QString &path)
{
    return m_nodyHash.contains(path);
}

QString INodyRenderer::render(const QString &path, const QJsonObject &object)
{
    if(m_nodyHash.contains(path)){
        return m_nodyHash[path]->execute(object, {});
    }
    return {};
}

QString INodyRenderer::getPage(IHttpStatusCode status)
{
    QString pagePath = QString(*m_userDefinedPrefix).append("/").append(IHttpStatus::toString(status)).append(".yky");
    if(isPathExist(pagePath)){
        return pagePath;
    }

    pagePath = QString(*m_userDefinedPrefix).append("/").append("errorPage.yky");
    if(isPathExist(pagePath)){
        return pagePath;
    }

    pagePath = QString(*m_defaultPrefix).append("/").append("errorPage.yky");
    if(isPathExist(pagePath)){
        return pagePath;
    }

    return {};
}

QString INodyRenderer::getPage(IResponseTemplateRenderer::PageType type)
{
    static const QMap<PageType, QString> PAGES{
        {PageType::Directory, "folder.yky"}
    };

    QString pagePath = QString(*m_userDefinedPrefix).append("/").append(PAGES[type]);
    if(isPathExist(pagePath)){
        return pagePath;
    }
    pagePath = QString(*m_defaultPrefix).append("/").append(PAGES[type]);
    if(isPathExist(pagePath)){
        return pagePath;
    }
    return {};
}

void INodyRenderer::addNody(const QString &path, INody *nody)
{
    m_nodyHash[path] = nody;
}


}
