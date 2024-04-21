#pragma once

#include "core/base/IHeaderUtil.h"
#include "IParamNode.h"
#include "http/net/IRequest.h"
#include "http/net/IResponse.h"

$PackageWebCoreBegin

struct IFunctionNode
{
public:
    static IFunctionNode createFunctionNode(std::function<void(const IRequest&, IResponse&)>);  
    // NOTE: 这个可以考虑通过重载定义 函数参数和返回值， 虽然也没啥意义。 除非我们之后对于这个内容进入深入的修改。
    // 也有意义， 之后考虑定义  std::function(QString(const IRequest&)) 这样的类型扩展
    // function 类型通过静态注册完成， 也可以通过函数中调用完成， 都可以的。

public:
    int returnTypeId {QMetaType::Void};
    int funParamCount{0};
    QVector<IParamNode> funParamNodes;
    std::function<void(IRequest&,  IResponse&)> function;
};

$PackageWebCoreEnd
