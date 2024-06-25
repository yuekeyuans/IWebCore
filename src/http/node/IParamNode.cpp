#include "IParamNode.h"
#include "http/node/IHttpParameterRestrictManage.h"
#include "http/node/IHttpParameterRestrictInterface.h"
#include "http/controller/IHttpManage.h"

$PackageWebCoreBegin

namespace detail {
    static const QStringList qualifierNames = {
        "mixed", "param", "url", "header", "body", "content",  "cookie", "session"
    };

    void checkQualifers(const QStringList& qualifers, const QString& type);
    IParamNode::Position getParamPosition(const QStringList& qualifiers);
}

IParamNode::IParamNode(int paramTypeId, QString paramTypeName, QString paramName)
    : paramTypeId(paramTypeId), paramTypeName(paramTypeName)
{

    auto arg = paramName.split("_$");
    paramName = arg.first();
    paramNameView = IHttpManage::instance()->stash(paramName.toUtf8());


    arg.pop_front();
    auto paramQualifiers = arg;
    detail::checkQualifers(paramQualifiers, paramTypeName);

    position = detail::getParamPosition(paramQualifiers);
    optional = paramQualifiers.contains("nullable");
}

QString IParamNode::getError()
{
    return m_error;
}

void detail::checkQualifers(const QStringList &qualifers, const QString& type)
{
    if(qualifers.length() != qualifers.toSet().size()){
        qFatal("error duplicated with controller function parameters");
    }

    if(qualifers.contains("nullable") && qualifers.contains("notnull")){
        qFatal("error option with controller function parameters");
    }

    bool exist{false};              // TODO: 这个理论上应该是可以的，但是，现在给禁止掉
    for(auto name : qualifierNames){
        if(qualifers.contains(name)){
            if(exist){
                qFatal("error multiple positon with controller function parameters ");
            }
            exist = true;
        }
    }

    const auto& userDefined = IHttpParameterRestrictManage::instance()->getRestrictNames();
    for(auto arg : qualifers){
        if(!qualifierNames.contains(arg) && !userDefined.contains(arg)){
            qFatal("error undefined qualifer with controller function parameters ");
        }
        if(userDefined.contains(arg)){
            auto obj = IHttpParameterRestrictManage::instance()->getInterface(arg);
            if(!obj->supportedTypes().contains(type)){
                qFatal("error unsupported type in user defined qualifer with controller function parameters ");
            }
        }
    }
}

IParamNode::Position detail::getParamPosition(const QStringList &qualifiers)
{
    int len= qualifierNames.length();
    for(int i=0; i<len; i++){
        if(qualifiers.contains(qualifierNames[i])){
            return IParamNode::Position(i);
        }
    }

    return IParamNode::Mixed;
}

$PackageWebCoreEnd
