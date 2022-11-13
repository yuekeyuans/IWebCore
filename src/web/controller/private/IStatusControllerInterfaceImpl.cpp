#include "IStatusControllerInterfaceImpl.h"

#include "web/controller/private/IControllerInfo.h"
#include "web/IWebAssert.h"

$PackageWebCoreBegin

$UseAssert(IWebAssert)

static const char* const StatusControllerPrefix = "iwebStatusFun$";

QVector<IStatusActionNode> IStatusControllerInterfaceImpl::generateStatusFunctionNodes(const IControllerInfo &info)
{
    QStringList funNames;
    QVector<IStatusActionNode> nodes;
    const auto& keys = info.clsInfo.keys();
    for(auto key : keys){
        if(key.startsWith(StatusControllerPrefix)){
            funNames.append(info.clsInfo[key]);
        }
    }

    for(const auto funName : funNames){
        QString key = QString(StatusControllerPrefix).append(funName).append('$').append("Status");
        if(!info.clsInfo.contains(key)){
            continue;
        }
        auto statusName = info.clsInfo[key];
        auto status = IHttpStatusHelper::toStatus(statusName);
        if(status == IHttpStatus::UNKNOWN){
            IAssertInfo astInfo;
            astInfo.function= funName;
            astInfo.reason = QString("statusName: ").append(statusName);
            $Ast->fatal("error_in_register_status_with_code", astInfo);
        }

        auto methodIter = std::find_if(info.methods.begin(), info.methods.end(), [=](const QMetaMethod& method){
            return method.name() == funName;
        });
        if(methodIter == info.methods.end()){
            IAssertInfo astInfo;
            astInfo.function = funName;
            $Ast->fatal("error_register_status_with_no_function", astInfo);
        }
        QMetaMethod method = *methodIter;

        IStatusActionNode node;
        node.httpStatus = status;
        node.methodNode = IMethodNode::fromMetaMethod(info.handler, info.className, method);
        nodes.append(node);
    }
    return nodes;
}

void IStatusControllerInterfaceImpl::checkStatusNodes(const QVector<IStatusActionNode> &nodes)
{
    for(const auto& node : nodes){
        checkStatusType(node);
        checkReturnType(node);
        checkInputArgs(node);
    }
}

void IStatusControllerInterfaceImpl::checkStatusType(const IStatusActionNode &node)
{
    if(node.httpStatus == IHttpStatus::OK_200){
        IAssertInfo info;
        info.function = node.methodNode.expression;
        info.reason = QString("curStatus: ").append(IHttpStatusHelper::toString(node.httpStatus));
        $Ast->fatal("register_status_not_allow_200_ok", info);
    }
}

void IStatusControllerInterfaceImpl::checkReturnType(const IStatusActionNode &node)
{
    if(node.methodNode.returnTypeId != QMetaType::Void){
        IAssertInfo info;
        info.function = node.methodNode.expression;
        info.returnType = node.methodNode.returnTypeName;
        $Ast->fatal("register_status_function_must_return_void", info);
    }
}

void IStatusControllerInterfaceImpl::checkInputArgs(const IStatusActionNode &node)
{
    const auto& typeNames = node.methodNode.getParamTypeNames();
    if(node.methodNode.getParamCount() == 2){
        if(typeNames.contains("IRequest&") && typeNames.contains("IResponse&") ){
            return;
        }
    }

    QStringList types;
    for(auto type : typeNames){
        types.append(type);
    }
    IAssertInfo info;
    info.paramterType = types.join(", ");
    $Ast->fatal("register_status_param_must_be_specific", info);
}

$PackageWebCoreEnd
