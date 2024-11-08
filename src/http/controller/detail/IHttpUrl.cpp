#include "IHttpUrl.h"
#include "core/util/ISpawnUtil.h"

$PackageWebCoreBegin

struct IHttpUrlDetail : public IHttpUrl
{
public:
    IHttpUrlDetail(const QString&);
};


namespace ISpawnUtil
{
    template<>
    IHttpUrl construct(QString data)
    {
        return IHttpUrlDetail(data);
    }

}

IHttpUrlDetail::IHttpUrlDetail(const QString &)
{

}


$PackageWebCoreEnd


