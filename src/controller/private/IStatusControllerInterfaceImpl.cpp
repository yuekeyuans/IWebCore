#include "IStatusControllerInterfaceImpl.h"

#include "core/assertion/IAssertDetail.h"
#include "core/assertion/IAssertPreProcessor.h"

$PackageWebCoreBegin

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

            IAssertDetail detail;
            detail[IAssertDetail::Function] = funName;
            detail["statusName"] = statusName;
            $AssertFatal(error_in_register_status_with_code, detail)

//            $Fatal().setMessage("there exist error in register status code class.")
//                    .setExtra("funName", funName)
//                    .setExtra("statusName", statusName)
//                    .fatal();
        }

        auto methodIter = std::find_if(methods.begin(), methods.end(), [=](const QMetaMethod& method){
            return method.name() == funName;
        });
        if(methodIter == methods.end()){
            IAssertDetail detail;
            detail[IAssertDetail::Function] = funName;
            $AssertFatal(error_register_status_with_no_function, detail)


//            $Fatal().setMessage("In define Status Intercept, can not find a certain function")
//                    .setExtra("certain funName", funName)
//                    .fatal();
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
        IAssertDetail detail;
        detail[IAssertDetail::Function] = node.functionNode.funExpression;
        detail["curStatus"] = IHttpStatusHelper::toString(node.httpStatus);
        $AssertFatal(register_status_not_allow_200_ok, detail)
    }
}

void IStatusControllerInterfaceImpl::checkReturnType(const IStatusFunctionNode &node)
{
    if(node.functionNode.funReturnTypeId != QMetaType::Void){
        IAssertDetail detail;
        detail[IAssertDetail::Function] = node.functionNode.funExpression;
        detail[IAssertDetail::ReturnType] = node.functionNode.funRetunType;
        $AssertFatal(register_status_function_must_return_void, detail)
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
    IAssertDetail detail;
    detail[IAssertDetail::Parameter] = types.join(", ");
    $AssertFatal(register_status_param_must_be_specific, detail)
}

$PackageWebCoreEnd
