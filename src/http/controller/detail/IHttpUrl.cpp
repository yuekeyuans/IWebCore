#include "IHttpUrl.h"
#include "core/util/ISpawnUtil.h"

$PackageWebCoreBegin

struct IHttpUrlDetail : public IHttpUrl
{
public:
    IHttpUrlDetail(const QStringList& args);
};

IHttpUrlDetail::IHttpUrlDetail(const QStringList& args)
{
    QStringList m_urlPieces;
    for(const QString& arg : args){
        if(!arg.trimmed().isEmpty() && arg.trimmed() != "/"){
            m_urlPieces.append(arg.trimmed());
        }
    }

    this->path = m_urlPieces.join("/").prepend("/");
    for(const QString piece : m_urlPieces){
        fragments.emplace_back(ISpawnUtil::construct<IHttpUrlFragment>(piece));
    }
}

namespace ISpawnUtil
{
    template<>
    IHttpUrl construct(QStringList args)
    {
        return IHttpUrlDetail(args);
    }
}

$PackageWebCoreEnd


