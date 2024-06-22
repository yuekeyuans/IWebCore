#include "IParamNode.h"

$PackageWebCoreBegin

namespace detail {
    static const QStringList qualifierNames = {
        "mixed", "param", "url", "header", "body", "content",  "cookie", "session"
    };

    void checkQualifers(const QStringList& qualifers);
    IParamNode::Position getParamPosition(const QStringList& qualifiers);
}

IParamNode::IParamNode(int paramTypeId, QString paramTypeName, QString paramName)
    : paramTypeId(paramTypeId), paramTypeName(paramTypeName)
{
    auto arg = paramName.split("_$");
    paramName = arg.first();
    arg.pop_front();
    paramQualifiers = arg;
    detail::checkQualifers(paramQualifiers);

    position = detail::getParamPosition(paramQualifiers);
    nullable = paramQualifiers.contains("nullable");
}

void detail::checkQualifers(const QStringList &qualifers)
{
    if(qualifers.length() != qualifers.toSet().size()){
        qFatal("error duplicated with controller function parameters");
    }

    if(qualifers.contains("nullable") && qualifers.contains("notnull")){
        qFatal("error option with controller function parameters");
    }

    // TODO: 这个理论上应该是可以的，但是，现在给禁止掉
    bool exist{false};
    for(auto name : qualifierNames){
        if(qualifers.contains(name)){
            if(exist){
                qFatal("error multiple positon with controller function parameters ");
            }
            exist = true;
        }
    }

    // 自定义用户注册的名称
}

IParamNode::Position detail::getParamPosition(const QStringList &qualifiers)
{
    int len= qualifierNames.length();
    for(int i=0; i<len; i++){
        if(qualifiers.contains(qualifierNames[i])){
            reutrn IParamNode::Position(i);
        }
    }

    return IParamNode::Mixed;
}

$PackageWebCoreEnd
