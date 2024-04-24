#pragma once

#include "IResponseInterface.h"
#include "IResponsePreProcessor.h"

$PackageWebCoreBegin

/**
 * 这个类区分于  IStatusResponse, 这个单纯表明他是运行时产生了错误，
 * IStatusResponse 需要被删除或修改， 因为IStatusReponse 即使404, 也不应该只是 返回 string 类型，其他类型也有可能
 */
class IInvalidResponse : public IResponseInterface<IInvalidResponse>
{
    $AsResponse(IInvalidResponse)
public:
    using IResponseInterface::operator[];
    using IResponseInterface::IResponseInterface;

public:
    IInvalidResponse() = default;
    IInvalidResponse(const QString& status, const QString& cause="");
    IInvalidResponse(int status, const QString& cause="");
};

$PackageWebCoreEnd
