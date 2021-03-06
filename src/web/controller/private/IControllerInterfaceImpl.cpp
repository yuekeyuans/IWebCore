#include "IControllerInterfaceImpl.h"

#include "core/bean/ITypeManage.h"
#include "web/net/IRequest.h"
#include "web/net/IResponse.h"
#include "web/IWebAssert.h"

$PackageWebCoreBegin

$UseAssert(IWebAssert)

namespace IControllerInterfaceImpHelper{
    bool isBeanType(const QString&);
    bool isSpecialTypes(const QString&);
    bool isParamNameWithSuffix(const QString& paramName);
    bool isIgnoreParamCheckFunction(const QString& funName, const QMap<QString, QString>& clsInfo);
}

void IControllerInterfaceImpl::checkUrlMappings(void *handler, const QMap<QString, QString> &clsInfo
                                                , const QVector<QMetaMethod> &methods)
{
    auto inst = instance();
    inst->checkMappingOverloadFunctions(methods);
    inst->checkMappingNameAndFunctionIsMatch(handler, clsInfo, methods);
    inst->checkMappingUrlIsValid(handler, clsInfo, methods);
    inst->checkMappingMethodArgsIsValid(handler, clsInfo, methods);
}

QVector<IUrlActionNode> IControllerInterfaceImpl::createMappingLeaves(
        void* handler, const QMap<QString, QString> &clsInfo,
        const QVector<QMetaMethod>& methods)
{
    QVector<IUrlActionNode> ret;

    auto inst = instance();
    auto infoList = inst->getMethodMappingInfo(clsInfo);
    std::for_each(infoList.begin(), infoList.end(), [&](const QStringList& info){
        ret.append(inst->createFunctionMappingLeaves(handler, info, clsInfo, methods));
    });
    return ret;
}

QVector<QStringList> IControllerInterfaceImpl::getMethodMappingInfo(const QMap<QString, QString> &clsInfo)
{
    static const QString CONTROLLER_INFO_PREFIX = "iwebControllerFun$";
    static const QString CONTROLLER_MAPPING_FLAG = "iwebControllerMapping$";

    QStringList rootPathArgs;
    if(clsInfo.contains(CONTROLLER_MAPPING_FLAG)){
        rootPathArgs =  clsInfo[CONTROLLER_MAPPING_FLAG].split("/");
    }

    QMap<QString, QMap<QString, QString>> infoMap;
    auto keys = clsInfo.keys();
    for(auto key : keys){
        if(!key.startsWith(CONTROLLER_INFO_PREFIX)){ continue; }
        auto args = key.split("$");
        auto funName = args[1];
        auto funType = args[2];
        infoMap[funName][funType] = clsInfo[key];
    }

    QVector<QStringList> ret;
    for(auto it = infoMap.begin(); it != infoMap.end(); ++it){
        ret.append(reformClsInfoArgs(it.value(), rootPathArgs));
    }
    return ret;
}

QStringList IControllerInterfaceImpl::reformClsInfoArgs(const QMap<QString, QString> &map
                                                        , const QStringList &rootPathArgs)
{
    QStringList ret;
    ret.append({map["resFunName"], map["reqMethod"]});

    for(int index =1 ;; index++){
        auto number = QString::number(index);
        if(!map.contains(number)){ break; }

        QStringList args(rootPathArgs);
        auto tempArgs = map[number].split("/");
        for(auto arg : tempArgs){
            arg = arg.trimmed();
            if(arg == "." || arg == ".."){
                $Ast->fatal("UrlError");
            }
            if(!arg.trimmed().isEmpty()){
                args.append(arg);
            }
        }
        ret.append(args.join("/"));
    }
    return ret;
}

QMap<QString, QString> IControllerInterfaceImpl::getStatusCodeInfos(QMap<QString, QString> clsInfos)
{
    static const QString PREFIX = "iwebControllerStatusCode$";
    QMap<QString, QString> ret;
    for(auto key : clsInfos.keys()){
        if(key.startsWith(PREFIX)){
            auto funName = key.split("$")[1];
            auto code = clsInfos[key];
            ret[code] = funName;
        }
    }
    return ret;
}

QVector<IUrlActionNode> IControllerInterfaceImpl::createFunctionMappingLeaves(void *handler, const QStringList &info
                                                                                , const QMap<QString, QString>& clsInfo
                                                                                , const QVector<QMetaMethod> &methods)
{
    QVector<IUrlActionNode> ret;

    IUrlActionNode node;
    auto funName = info.first();
    node.ignoreParamCheck = IControllerInterfaceImpHelper::isIgnoreParamCheckFunction(funName, clsInfo);
    node.httpMethod = IHttpMethodHelper::toMethod(info[1]);
    for(auto& method : methods){
        if(method.name() == funName){
            node.methodNode = IMethodNode::fromMetaMethod(handler, method);
        }
    }
    for(auto i=2; i<info.length(); i++){
        node.url = info[i].trimmed().isEmpty() ? "/" : info[i];  // exclude empty url
        ret.append(node);
    }
    return ret;
}

void IControllerInterfaceImpl::checkMappingOverloadFunctions(const QVector<QMetaMethod> &methods)
{
    QStringList names;
    for(const auto& method : methods){
        if(names.contains(method.name())){
            IAssertInfo info;
            info.reason = QString("name: ").append(method.name());
            $Ast->fatal("OverloadOrDefaultValueFunctionNotSupported", info);
        }
        names.append(method.name());
    }
}

void IControllerInterfaceImpl::checkMappingNameAndFunctionIsMatch(void *handler, const QMap<QString, QString> &clsInfo
                                                                  , const QVector<QMetaMethod> &methods)
{
    Q_UNUSED(handler)
    QStringList methodNames;
    for(const auto& method : methods){
        methodNames.append(method.name());
    }

    auto infos = getMethodMappingInfo(clsInfo);
    for(const auto& info : infos){
        auto name = info.first();
        if(!methodNames.contains(name)){
            IAssertInfo info;
            info.reason = QString("name: ").append(name);
            $Ast->fatal("MappingMismatchFatal", info);
        }
    }
}

void IControllerInterfaceImpl::checkMappingUrlIsValid(void *handler, const QMap<QString, QString> &clsInfo
                                                      , const QVector<QMetaMethod> &methods)
{
    Q_UNUSED(handler)
    Q_UNUSED(methods);
    auto infos = getMethodMappingInfo(clsInfo);
    for(auto info : infos){
        std::for_each(info.begin() + 2, info.end(), [&](const QString& url){
            chekcUrlErrorCommon(url);
            CheckUrlErrorWildCard(url);
        });
    }
}

void IControllerInterfaceImpl::checkMappingMethodArgsIsValid(void *handler, const QMap<QString, QString> &clsInfo
                                                             , const QVector<QMetaMethod> &methods)
{
    using CheckFunType = void (IControllerInterfaceImpl::*)(const IUrlActionNode&);
    static QList<CheckFunType> funs = {
        &IControllerInterfaceImpl::chechMethodSupportedReturnType,
        &IControllerInterfaceImpl::checkMethodSupportedParamArgType,
        &IControllerInterfaceImpl::checkMethodArgNameIntegrality,
        &IControllerInterfaceImpl::checkMethodOfReturnVoid,
        &IControllerInterfaceImpl::checkMethodBodyContentArgs,
        &IControllerInterfaceImpl::checkMethodParamterWithSuffixProper,
        &IControllerInterfaceImpl::checkMethodParamterWithSuffixSet,
    };

    auto leaves = createMappingLeaves(handler, clsInfo, methods);
    for(auto& leaf : leaves){
        for(auto& fun : funs){
            std::mem_fn(fun)(this, leaf);
        }
    }
}

void IControllerInterfaceImpl::chekcUrlErrorCommon(const QString &url)
{
    static QRegularExpression wildcard("^<.*>$");
    static QRegularExpression urlPieceReg("^[0-9a-zA-Z\\$\\.\\+\\*\\(\\)\\,!_\\$']+$");    // TODO: I don`t know whether it right or not see: https://www.cnblogs.com/cxygg/p/9278542.html
    auto pieces = url.split('/');

    for(const auto& piece : pieces){
        if(piece.isEmpty()){
            continue;
        }
        if(wildcard.match(piece).hasMatch()){ // do not check wild card.
            continue;
        }

        if(!urlPieceReg.match(piece).hasMatch()){
            IAssertInfo info;
            info.reason = QString("url: ").append(url);
            $Ast->fatal("UrlInvalidCharacter", info);
        }

        if(piece == "." || piece == ".."){
            IAssertInfo info;
            info.reason = QString("url: ").append(url).append(" piece: ").append(piece);
            $Ast->fatal("UrlError", info);
        }

        if(piece.contains(' ') || piece.contains('\t')){
            IAssertInfo info;
            info.reason = QString("url: ").append(url);
            $Ast->fatal("UrlBlankCharacter", info);
        }
    }
}

void IControllerInterfaceImpl::CheckUrlErrorWildCard(const QString url)
{
    static QRegularExpression validName("^[0-9a-zA-Z_]+$");
    static QRegularExpression conoExpression0("^<(.*)>$");
    static QRegularExpression conoExpression1("^<(.*):(.*)>$");
    static QRegularExpression conoExpression2("^<(reg)?:(.*):(.*)>$");

    auto pieces = url.split('/');
    for(auto& piece : pieces){
        if(!(piece.startsWith('<') && piece.endsWith('>'))){
            continue;
        }
        int conoCount = piece.count(':');
        if(conoCount == 0){
            auto result = conoExpression0.match(url);
            if(result.hasMatch()){
                auto name = result.captured(1);
                if(!validName.match(name).isValid()){
                    QString info = "not a valid name in wideCard expression:\n\t" + url;
                    qFatal(info.toUtf8());
                }
            }
        } else if(conoCount == 1){
            auto result = conoExpression1.match(url);
            auto name = result.captured(1);
            auto validator = result.captured(2);
            if(!validName.match(name).isValid() || !validName.match(validator).isValid()){
                QString info = "not a valid name or validator name in wideCard expression:\n\t" + url;
                qFatal(info.toUtf8());
            }
        } else if(conoCount == 2){
            auto result = conoExpression2.match(url);
            if(!result.hasMatch()){
                QString info = "not a valid regexpression wideCard expression:\n\t" + url;
                qFatal(info.toUtf8());
            }
            auto name = result.captured(2);
            auto regexp = result.captured(3);
            if(!validName.match(name).isValid()){
                QString info = "not a valid name in wideCard expression:\n\t" + url;
                qFatal(info.toUtf8());
            }
            QRegularExpression exp(regexp);
            if(!exp.isValid()){
                QString info = "not a valid regexp in wideCard expression:\n\t" + url;
                qFatal(info.toUtf8());
            }
        }else {
            QString info = "wideCard do not supoort for expression more than two conos: \n\t" + url;
            qFatal(info.toUtf8());
        }
    }
}

// ref to IControllerFunctionBase.cpp
void IControllerInterfaceImpl::chechMethodSupportedReturnType(const IUrlActionNode &node)
{
    const static QString info = "this kind of return type not supported, please change the return type! valid types are :\n\t"
                   "[void, int, QString, QJsonArray, QJsonObject, QJsonValue, QByteArray, QStringList, IxxxxResponse]\n\t";

    const static  QVector<QMetaType::Type> validMetaType = {
        QMetaType::Void,
        QMetaType::Int,
        QMetaType::QString,
        QMetaType::QJsonArray,
        QMetaType::QJsonObject,
        QMetaType::QJsonValue,
        QMetaType::QByteArray,
//        QMetaType::QStringList,
    };

    auto type = node.methodNode.returnTypeName;
    auto id = node.methodNode.returnTypeId;
    if(id == QMetaType::UnknownType){
        auto errorInfo = info + "the error take place in Function : " + node.methodNode.funName;
        qFatal(errorInfo.toUtf8());
    }

    if(validMetaType.contains(id)){
        return;
    }

    if(type.startsWith("I") && type.endsWith("Response")){
        return;
    }

    auto errorInfo = info + "the error take place in Function : " + node.methodNode.funName;
    qFatal(errorInfo.toUtf8());
}

// 规定传入值类型： see: 输入参数列表
void IControllerInterfaceImpl::checkMethodSupportedParamArgType(const IUrlActionNode &node)
{
    static const QString info = "the argument type is not valid, please use the correct type\n";
    static const QVector<QMetaType::Type> allowType = {
        QMetaType::Bool,
        QMetaType::Short,
        QMetaType::UShort,
        QMetaType::Int,
        QMetaType::UInt,
        QMetaType::Long,
        QMetaType::ULong,
        QMetaType::LongLong,
        QMetaType::ULongLong,
        QMetaType::Float,
        QMetaType::Double,

        QMetaType::QString,
        QMetaType::QByteArray,

        QMetaType::QJsonArray,
        QMetaType::QJsonObject,
        QMetaType::QJsonValue,
    };

    const auto& typeNames = node.methodNode.getParamTypeNames();
    const auto& typeIds = node.methodNode.getParamTypeIds();
    const auto& count = node.methodNode.getParamCount();
    for(int i=0; i<count; i++) {
        QString typeName = typeNames[i];
        auto typeId = typeIds[i];

        if(typeId >= QMetaType::User){
            bool isSupportedType = IControllerInterfaceImpHelper::isSpecialTypes(typeName)
                                   || IControllerInterfaceImpHelper::isBeanType(typeName);
            if(!isSupportedType){
                IAssertInfo info;
                info.reason = QString("At Function: ").append(node.methodNode.expression)
                                   .append(" At Param: ").append(typeName);
                $Ast->fatal("controller_check_param_Type_has_unsupported_user_defined_type", info);
            }
        } else{
            if(!allowType.contains(typeId)){
                IAssertInfo info;
                info.reason = QString("At Function: ").append(node.methodNode.expression)
                                   .append(" At Param: ").append(typeName);
                $Ast->fatal("controller_check_param_Type_has_unsupported_inner_type", info);
            }
        }
    }
}

void IControllerInterfaceImpl::checkMethodArgNameIntegrality(const IUrlActionNode &node)
{
    static const  QString info = "the controller function`s parameter should always define it`s name, the name can`t be omitted,\n\t"
                          "the error happened in Function : ";

    auto paramNames = node.methodNode.getParamNames();
    for(auto& name : paramNames){
        if(name.isEmpty()){
            auto funInfo = info + node.methodNode.funName;
            qFatal(funInfo.toUtf8());
        }
    }
}

void IControllerInterfaceImpl::checkMethodOfReturnVoid(const IUrlActionNode &node)
{
    if(node.methodNode.returnTypeId != QMetaType::Void){
        return;
    }

    auto typeNames = node.methodNode.getParamTypeNames();
    if(!typeNames.contains("IResponse") && !typeNames.contains("IResponse&")){
        QString info = "mapping function that return void should include IResponse in side function parameters\n"
                    "at Function : " + node.methodNode.funName;
        qFatal(info.toUtf8());
    }
}

// 检查特殊的引用
void IControllerInterfaceImpl::checkMethodBodyContentArgs(const IUrlActionNode &node)
{
    const auto& typeNames = node.methodNode.getParamTypeNames();

    auto index = typeNames.indexOf("QJsonValue&");
    if(index != -1){
        const auto& paramNames = node.methodNode.getParamNames();
        auto name = paramNames[index];
        if(!name.endsWith("_content")){
            QString info = "QJsonValue& can`t be used except in $Body expression\n"
                           "at Function : " + node.methodNode.funName;
            qFatal(info.toUtf8());
        }
    }
}

void IControllerInterfaceImpl::checkMethodParamterWithSuffixProper(const IUrlActionNode &node)
{
    const auto& argNodes = node.methodNode.paramNodes;

    // get 中不能调用 body 的参数。
    if(node.httpMethod == IHttpMethod::GET){
        for(const auto& param : argNodes){
            if(param.paramName.endsWith("_body") || param.paramName.endsWith("_content")){
                IAssertInfo info;
                info.reason = QString("At Function: ").append(node.methodNode.expression).append(" Parameter: ").append(param.paramName);
                $Ast->fatal("controller_method_get_but_want_body_content", info);
            }
        }
    }
}

void IControllerInterfaceImpl::checkMethodParamterWithSuffixSet(const IUrlActionNode &node)
{
    static const QStringList externalTypes ={
        "IRequest", "IRequest&",
        "IResponse", "IResponse&",
        "IMultiPart", "IMultiPart&",
        "ICookieJar", "ICookieJar&",
        "ISessionJar", "ISessionJar&"
        "QJsonValue", "QJsonValue&"
    };
    if(node.ignoreParamCheck){
        return;
    }
    const auto& nodes = node.methodNode.paramNodes;
    for(auto param : nodes){
        if(!externalTypes.contains(param.paramTypeName)){
            if(!IControllerInterfaceImpHelper::isParamNameWithSuffix(param.paramName)){
                IAssertInfo info;
                info.reason = QString("At Function: ").append(node.methodNode.expression)
                                   .append(" At Param: ").append(param.paramName);
                $Ast->fatal("irequest_controller_function_with_param_not_marked", info);
            }
        }
    }
}

bool IControllerInterfaceImpHelper::isSpecialTypes(const QString& typeName)
{
    static const QStringList specialExternalTypes = {
        "IRequest",     "IRequest&",
        "IResponse",    "IResponse&",
        "IMultiPart",   "IMultiPart&",
        "ICookieJar",   "ICookieJar&",
        "ISessionJar",  "ISessionJar&",
        "IHeaderJar",   "IHeaderJar&"
    };

    return specialExternalTypes.contains(typeName);
}

bool IControllerInterfaceImpHelper::isBeanType(const QString& typeName)
{
    return ITypeManage::containBean(typeName);
}

bool IControllerInterfaceImpHelper::isParamNameWithSuffix(const QString& paramName)
{
    static const QStringList suffixes = {
        "_mixed", "_param", "_url", "_body", "_content", "_header",
        "_cookie", "_session", "_app", "_system"
    };

    for(const auto& suffix : suffixes){
        if(paramName.endsWith(suffix)){
            return true;
        }
    }
    return false;
}

bool IControllerInterfaceImpHelper::isIgnoreParamCheckFunction(const QString& funName
                                                               , const QMap<QString, QString>& clsInfo)
{
    static const QString ignoreAllKey = "ignore_all_controller_fun_name";
    static const QString suffix = "ignore_controller_fun_name_";

    if(clsInfo.contains(ignoreAllKey)){
        return true;
    }

    auto key = suffix + funName;
    return clsInfo.contains(key);
}

$PackageWebCoreEnd
