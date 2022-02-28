#include "IStatusControllerInterfaceImpl.h"
#include "base/IConstantUtil.h"
#include "log/IFatalInfo.h"

$PackageWebCoreBegin

QVector<IStatusFunctionNode> IStatusControllerInterfaceImpl::generateStatusFunctionNodes(void *handle, QMap<QString, QString> clsInfo, QVector<QMetaMethod> methods)
{
    QStringList funNames;
    QVector<IStatusFunctionNode> nodes;
    const auto& keys = clsInfo.keys();
    for(auto key : keys){
        if(key.startsWith(IConstantUtil::StatusControllerPrefix)){
            funNames.append(clsInfo[key]);
        }
    }

    for(const auto funName : funNames){
        QString key = QString(IConstantUtil::StatusControllerPrefix).append(funName).append('$').append("Status");
        if(!clsInfo.contains(key)){
            continue;
        }
        auto statusName = clsInfo[key];
        auto status = IHttpStatusHelper::toStatus(statusName);
        if(status == IHttpStatus::UNKNOWN){
            $Fatal().setMessage("there exist error in register status code class.")
                    .setExtra("funName", funName)
                    .setExtra("statusName", statusName)
                    .fatal();
        }

        auto methodIter = std::find_if(methods.begin(), methods.end(), [=](const QMetaMethod& method){
            return method.name() == funName;
        });
        if(methodIter == methods.end()){
            $Fatal().setMessage("In define Status Intercept, can not find a certain function")
                    .setExtra("certain funName", funName)
                    .fatal();
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
        $Fatal().setMessage("In define Status Intercept, status type are not allowed to be 200 (ok)")
                .setExtra("function signature", node.functionNode.funExpression)
                .setExtra("current status", IHttpStatusHelper::toString(node.httpStatus))
                .fatal();
    }
}

void IStatusControllerInterfaceImpl::checkReturnType(const IStatusFunctionNode &node)
{
    if(node.functionNode.funReturnTypeId != QMetaType::Void){
        $Fatal().setMessage("In define Status Intercept, return type must be void")
                .setExtra("function signature", node.functionNode.funExpression)
                .setExtra("current return type",  node.functionNode.funRetunType)
                .fatal();
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
    $Fatal().setMessage("In define Status Intercept, the parameter type must be IRequest& and IResponse&")
            .setExtra("current parameter type", types.join(", "))
            .fatal();
}

$PackageWebCoreEnd
