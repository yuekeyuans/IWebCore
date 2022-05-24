#include "IStatusControllerInterfaceImpl.h"

#include "web/IWebAst.h"

$PackageWebCoreBegin

$UseAst(IWebAst)

static const char* const StatusControllerPrefix = "iwebStatusFun$";

QVector<IStatusFunctionNode> IStatusControllerInterfaceImpl::generateStatusFunctionNodes(void *handle, QMap<QString, QString> clsInfo, QVector<QMetaMethod> methods)
{
    QStringList funNames;
    QVector<IStatusFunctionNode> nodes;
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
            IAstInfo info;
            info.function= funName;
            info.reason = QString("statusName: ").append(statusName);
            $Ast->fatal("error_in_register_status_with_code", info);
        }

        auto methodIter = std::find_if(methods.begin(), methods.end(), [=](const QMetaMethod& method){
            return method.name() == funName;
        });
        if(methodIter == methods.end()){
            IAstInfo info;
            info.function = funName;
            $Ast->fatal("error_register_status_with_no_function", info);
        }
        QMetaMethod method = *methodIter;

        IStatusFunctionNode node;
        node.httpStatus = status;
        node.functionNode = IFunctionNode::fromMetaMethod(handle,method);
        nodes.append(node);
    }
    return nodes;
}

void IStatusControllerInterfaceImpl::checkStatusNodes(const QVector<IStatusFunctionNode> &nodes)
{
    auto inst = instance();
    for(const auto& node : nodes){
        inst->checkStatusType(node);
        inst->checkReturnType(node);
        inst->checkInputArgs(node);
    }
}

void IStatusControllerInterfaceImpl::checkStatusType(const IStatusFunctionNode &node)
{
    if(node.httpStatus == IHttpStatus::OK_200){
        IAstInfo info;
        info.function = node.functionNode.funExpression;
        info.reason = QString("curStatus: ").append(IHttpStatusHelper::toString(node.httpStatus));
        $Ast->fatal("register_status_not_allow_200_ok", info);
    }
}

void IStatusControllerInterfaceImpl::checkReturnType(const IStatusFunctionNode &node)
{
    if(node.functionNode.funReturnTypeId != QMetaType::Void){
        IAstInfo info;
        info.function = node.functionNode.funExpression;
        info.returnType = node.functionNode.funRetunType;
        $Ast->fatal("register_status_function_must_return_void", info);
    }
}

void IStatusControllerInterfaceImpl::checkInputArgs(const IStatusFunctionNode &node)
{
    if(node.functionNode.funParamCount == 2){
        if(node.functionNode.funParamTypes.contains("IRequest&")
                && node.functionNode.funParamTypes.contains("IResponse&") ){
            return;
        }
    }

    QStringList types;
    for(auto type : node.functionNode.funParamTypes){
        types.append(type);
    }
    IAstInfo info;
    info.paramterType = types.join(", ");
    $Ast->fatal("register_status_param_must_be_specific", info);
}

$PackageWebCoreEnd
