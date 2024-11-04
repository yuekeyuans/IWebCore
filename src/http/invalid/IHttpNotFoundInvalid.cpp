#include "IHttpNotFoundInvalid.h"

$PackageWebCoreBegin

IHttpNotFoundInvalid::IHttpNotFoundInvalid()
    : IHttpInvalidInterface(IHttpStatus::NOT_FOUND_404)
{
}

IHttpNotFoundInvalid::IHttpNotFoundInvalid(QString description)
    : IHttpInvalidInterface(IHttpStatus::NOT_FOUND_404, description)
{
}

void IHttpNotFoundInvalid::process(IRequest &)
{
    // TODO: 这里需要完成数据的处理，而这里的处理将会放置 IHttpManage 中注册。
    // 之后再搞这些边边角角的内容。
    qDebug() << "calll here";
}

$PackageWebCoreEnd
