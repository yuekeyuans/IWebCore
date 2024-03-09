#include "IControllerInterfaceImpl.h"

#include "core/bean/IBeanTypeManage.h"
#include "web/controller/private/IControllerInfo.h"
#include "web/net/IRequest.h"
#include "web/net/IResponse.h"
#include "web/IWebAssert.h"

$PackageWebCoreBegin

$UseAssert(IWebAssert)

namespace IControllerInterfaceImpHelper{
    struct MappingInfo{
        QString funName;
        QStringList path;
        IHttpMethod method;
        int index;
    };

    bool isBeanType(const QString&);
    bool isSpecialTypes(const QString&);
    bool isParamNameWithSuffix(const QString& paramName);
    bool isIgnoreParamCheckFunction(const QString& funName, const QMap<QString, QString>& clsInfo);

    QVector<MappingInfo> getMethodMappingInfo(const QMap<QString, QString> &clsInfo);
    QStringList toNormalUrl(const QString& url, const QStringList& prefix);
    QVector<IUrlActionNode> createFunctionMappingLeaves(const IControllerInfo& info, const MappingInfo& mapping);
}
using namespace IControllerInterfaceImpHelper;

void IControllerInterfaceImpl::checkUrlMappings(const IControllerInfo& info)
{
    auto inst = instance();
    inst->checkMappingOverloadFunctions(info.classMethods);
    inst->checkMappingNameAndFunctionIsMatch(info);
    inst->checkMappingUrlIsValid(info);
    inst->checkMappingMethodArgsIsValid(info);
}

QVector<IUrlActionNode> IControllerInterfaceImpl::createMappingLeaves(const IControllerInfo& info)
{
    QVector<IUrlActionNode> ret;
    auto args = getMethodMappingInfo(info.classInfo);
    for(const auto& arg : args){
        ret.append(createFunctionMappingLeaves(info, arg));
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

void IControllerInterfaceImpl::checkMappingNameAndFunctionIsMatch(const IControllerInfo& info)
{
    QStringList methodNames;
    for(const auto& method : info.classMethods){
        methodNames.append(method.name());
    }
    auto infos = getMethodMappingInfo(info.classInfo);
    QStringList infoNames;
    for(const auto& info : infos){
        infoNames.append (info.funName);
    }

    for(const auto& name : infoNames){
        if(!methodNames.contains(name)){
            IAssertInfo info;
            info.reason = QString("name: ").append(name);
            $Ast->fatal("MappingMismatchFatal", info);
        }
    }
}

void IControllerInterfaceImpl::checkMappingUrlIsValid(const IControllerInfo &info)
{
    auto infos = getMethodMappingInfo(info.classInfo);
    for(const MappingInfo& info : infos){
        std::for_each(info.path.begin(), info.path.end(), [&](const QString& url){
            chekcUrlErrorCommon(url);
            CheckUrlErrorWildCard(url);
        });
    }
}

void IControllerInterfaceImpl::checkMappingMethodArgsIsValid(const IControllerInfo& info)
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

    auto leaves = createMappingLeaves(info);
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

// 检测是否可以添加后缀类型
void IControllerInterfaceImpl::checkMethodParamterWithSuffixSet(const IUrlActionNode &node)
{
    static const QStringList externalTypes ={
        "IRequest",     "IRequest&",
        "IResponse",    "IResponse&",
        "IMultiPart",   "IMultiPart&",
        "ICookieJar",   "ICookieJar&",
        "ICookiePart",  "ICookiePart&",
        "IHeaderJar",   "IHeaderJar&",
        "ISessionJar",  "ISessionJar&",
        "QJsonValue",   "QJsonValue&",
    };
    if(node.ignoreParamCheck){
        return;
    }
    const auto& nodes = node.methodNode.paramNodes;
    for(auto param : nodes){
        if(externalTypes.contains(param.paramTypeName)){
            continue;
        }

        if(!IControllerInterfaceImpHelper::isParamNameWithSuffix(param.paramName)){
            IAssertInfo info;
            info.reason = QString("At Function: ").append(node.methodNode.expression)
                              .append(" At Param: ").append(param.paramName);
            $Ast->warn("irequest_controller_function_with_param_not_marked", info);
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
        "ICookiePart",  "ICookiePart&"
        "ISessionJar",  "ISessionJar&",
        "IHeaderJar",   "IHeaderJar&"
    };

    return specialExternalTypes.contains(typeName);
}

bool IControllerInterfaceImpHelper::isBeanType(const QString& typeName)
{
    return IBeanTypeManage::containBean(typeName);
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

QVector<MappingInfo> IControllerInterfaceImpHelper::getMethodMappingInfo(const QMap<QString, QString> &clsInfo)
{
    static const QString CONTROLLER_MAPPING_FLAG = "iwebControllerMapping$";
    QStringList rootPathArgs;
    if(clsInfo.contains(CONTROLLER_MAPPING_FLAG)){
        rootPathArgs =  clsInfo[CONTROLLER_MAPPING_FLAG].split("/");
    }

    static const QString CONTROLLER_INFO_PREFIX = "iwebControllerFun$";
    QVector<MappingInfo> infos;
    auto keys = clsInfo.keys();
    for(auto key : keys){
        if(key.startsWith(CONTROLLER_INFO_PREFIX)){
            QStringList args = key.split("$");
            MappingInfo info{
                args[1],
                toNormalUrl(clsInfo[key], rootPathArgs),
                IHttpMethodHelper::toMethod(args[2]),
                args[3].toInt()
            };

            infos.append(info);
        }
    }

    return infos;
}

QStringList IControllerInterfaceImpHelper::toNormalUrl(const QString& url, const QStringList& prefix)
{
    QStringList ret = prefix;
    auto tempArgs = url.split("/");
    for(auto arg : tempArgs){
        arg = arg.trimmed();
        if(arg == "." || arg == ".."){
            $Ast->fatal("UrlError");
        }
        if(!arg.trimmed().isEmpty()){
            ret.append(arg);
        }
    }
    if(ret.isEmpty()){
        ret.append("/");
    }
    return ret;
}

QVector<IUrlActionNode> IControllerInterfaceImpHelper::createFunctionMappingLeaves(const IControllerInfo& info, const MappingInfo& mapping)
{
    QVector<IUrlActionNode> ret;

    IUrlActionNode node;
    auto funName = mapping.funName;
    node.ignoreParamCheck = IControllerInterfaceImpHelper::isIgnoreParamCheckFunction(funName, info.classInfo);
    node.httpMethod = mapping.method;
    QStringList pieces;
    for(const auto& method : info.classMethods){
        if(method.name() == funName){
            node.methodNode = IMethodNode::fromMetaMethod(info.handler, info.className, method);
        }
    }
    for(const QString& arg : mapping.path){
        if(arg.trimmed().isEmpty() || arg.trimmed() == "/"){
            continue;
        }
        pieces.append(arg.trimmed());
    }
    node.url = pieces.join("/").prepend("/");
    ret.append(node);
    return ret;
}

$PackageWebCoreEnd
