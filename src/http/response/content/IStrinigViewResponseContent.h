#pragma once

#include "IResponseContentWare.h"
#include "core/unit/IClassNameUnit.h"

$PackageWebCoreBegin

// TODO: 这个可以随着 IStringData 出现，删除掉了，这其中包括 ByteArray, std::string, IStringView, 甚至是 QString, 等各种类型。
class IStrinigViewResponseContent : public IResponseContentWare, private IClassNameUnit<IStrinigViewResponseContent>
{
public:
    IStrinigViewResponseContent(IStringView);

public:
    virtual const std::string& getType() const final;
    virtual const std::string& getSuggestedMime() const final;
};

$PackageWebCoreEnd
