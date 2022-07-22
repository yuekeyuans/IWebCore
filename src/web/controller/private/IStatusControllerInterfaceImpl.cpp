#include "IStatusControllerInterfaceImpl.h"

#include "web/IWebAssert.h"

$PackageWebCoreBegin

$UseAssert(IWebAssert)

static const char* const StatusControllerPrefix = "iwebStatusFun$";

QVector<IStatusActionNode> IStatusControllerInterfaceImpl::generateStatusFunctionNodes(void *handle, QMap<QString, QString> clsInfo, QVector<QMetaMethod> methods)
{
    QStringList funNames;
    QVector<IStatusActionNode> nodes;
    const auto& keys = clsInfo.keys();
    for(auto key : keys){
        if(key.startsWith(StatusControllerPrefix)){
            funNames.append(clsInfo[key]);
        }
    }

    for(const auto funName : funNames){
        QString key = QString(StatusControllerPrefix).append(funName).append('$').append("Status");
        if(!clsInfo.contains(key)){
            continue;
        }
        auto statusName = clsInfo[key];
        auto status = IHttpStatusHelper::toStatus(statusName);
        if(status == IHttpStatus::UNKNOWN){
            IAssertInfo info;
            info.function= funName;
            info.reason = QString("statusName: ").append(statusName);
            $Ast->fatal("error_in_register_status_with_code", info);
        }

        auto methodIter = std::find_if(methods.begin(), methods.end(), [=](const QMetaMethod& method){
            return method.name() == funName;
        });
        if(methodIter == methods.end()){
            IAssertInfo info;
            info.function = funName;
            $Ast->fatal("error_register_status_with_no_function", info);
        }
        QMetaMethod method = *methodIter;

        IStatusActionNode node;
        node.httpStatus = status;
        node.methodNode = IMethodNode::fromMetaMethod(handle,method);
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
        info.function = node.methodNode.funExpression;
        info.reason = QString("curStatus: ").append(IHttpStatusHelper::toString(node.httpStatus));
        $Ast->fatal("register_status_not_allow_200_ok", info);
    }
}

void IStatusControllerInterfaceImpl::checkReturnType(const IStatusActionNode &node)
{
    if(node.methodNode.funReturnTypeId != QMetaType::Void){
        IAssertInfo info;
        info.function = node.methodNode.funExpression;
        info.returnType = node.methodNode.funRetunType;
        $Ast->fatal("register_status_function_must_return_void", info);
    }
}

void IStatusControllerInterfaceImpl::checkInputArgs(const IStatusActionNode &node)
{
    if(node.methodNode.funParamCount == 2){
        if(node.methodNode.funParamTypes.contains("IRequest&")
                && node.methodNode.funParamTypes.contains("IResponse&") ){
            return;
        }
    }

    QStringList types;
    for(auto type : node.methodNode.funParamTypes){
        types.append(type);
    }
    IAssertInfo info;
    info.paramterType = types.join(", ");
    $Ast->fatal("register_status_param_must_be_specific", info);
}

$PackageWebCoreEnd
