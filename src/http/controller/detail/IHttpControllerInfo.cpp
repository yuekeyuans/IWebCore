#include "IHttpControllerInfo.h"
#include "core/bean/IBeanTypeManage.h"
#include "core/util/ISpawnUtil.h"
#include "http/controller/IHttpControllerAbort.h"
#include "http/biscuits/IHttpMethod.h"
#include "http/controller/detail/IHttpControllerActionNode.h"

$PackageWebCoreBegin

class IHttpControllerInfoDetail : public IHttpControllerInfo
{
    struct MethodMappingInfo
    {
        MethodMappingInfo(const QString& key, const QString& value, const QStringList&rootPath);
        QStringList toNormalUrl(const QString& url, const QStringList& prefix);
        QString funName;
        QStringList path;
        IHttpMethod method;
        int index;
    };
public:
    IHttpControllerInfoDetail(void *handler, const QString &className,
                              const QMap<QString, QString> &classInfo,
                              const QVector<QMetaMethod> &methods);
private:
    void parseMapppingInfos();
    void parseMappingLeaves();

private:
    void checkMapping();
    void checkMappingOverloadFunctions();
    void checkMappingNameAndFunctionIsMatch();
    void checkMappingUrl();
    void checkMappingUrlErrorCommon(const QString& url);
    void CheckMappingUrlErrorWildCard(const QString& url);

private:
    void checkMethod();
    void chechMethodSupportedReturnType(const IHttpControllerActionNode& node);
    void checkMethodSupportedParamArgType(const IHttpControllerActionNode& node);
    void checkMethodOfReturnVoid(const IHttpControllerActionNode& node);
    void checkMethodBodyContentArgs(const IHttpControllerActionNode& node);
    void checkMethodParamterWithSuffixProper(const IHttpControllerActionNode& node);

private:
    bool isSpecialTypes(const QString&);

private:
    QStringList parseRootPathArgs();
    QVector<IHttpControllerActionNode> createFunctionMappingLeaves(const MethodMappingInfo& mapping);

private:
    QVector<MethodMappingInfo> m_mappingInfos;
};


IHttpControllerInfoDetail::MethodMappingInfo::MethodMappingInfo(const QString &key, const QString &value, const QStringList& rootPath)
{
    auto args = key.split("$");
    index = args.last().toInt();
    args.pop_back();
    method = IHttpMethodUtil::toMethod(args.last());
    args.pop_back();
    args.pop_front();
    funName = args.join("$");
    path = toNormalUrl(value, rootPath);
}

QStringList IHttpControllerInfoDetail::MethodMappingInfo::toNormalUrl(const QString &url, const QStringList &prefix)
{
    QStringList ret = prefix;
    auto tempArgs = url.split("/");
    for(auto arg : tempArgs){
        arg = arg.trimmed();
        if(arg == "." || arg == ".."){
            IHttpControllerAbort::abortUrlError($ISourceLocation);
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

IHttpControllerInfoDetail::IHttpControllerInfoDetail(void *handler_, const QString &className_, const QMap<QString, QString> &classInfo_, const QVector<QMetaMethod> &methods_)
{
    this->handler = handler_;
    this->className = className_;
    this->classInfo = classInfo_;
    this->classMethods = methods_;

    parseMapppingInfos();
    parseMappingLeaves();
}

void IHttpControllerInfoDetail::parseMapppingInfos()
{
    static constexpr char CONTROLLER_INFO_PREFIX[] = "IHttpControllerFunMapping$";
    auto rootPath = parseRootPathArgs();
    auto keys = classInfo.keys();
    for(auto key : keys){
        if(key.startsWith(CONTROLLER_INFO_PREFIX)){
            m_mappingInfos.append({key, classInfo[key], rootPath});
        }
    }

    checkMapping();
}

void IHttpControllerInfoDetail::parseMappingLeaves()
{
    for(const auto& arg : m_mappingInfos){
        m_urlNodes.append(createFunctionMappingLeaves(arg));
    }

    checkMethod();
}


void IHttpControllerInfoDetail::checkMapping()
{
    checkMappingOverloadFunctions();
    checkMappingNameAndFunctionIsMatch();
    checkMappingUrl();
}

void IHttpControllerInfoDetail::checkMappingOverloadFunctions()
{
    QStringList names;
    for(const auto& method : classMethods){
        if(names.contains(method.name())){
            IHttpControllerAbort::abortOverloadOrDefaultValueFunctionNotSupported(QString("duplicated function name: ").append(method.name()), $ISourceLocation);
        }
        names.append(method.name());
    }
}

void IHttpControllerInfoDetail::checkMappingNameAndFunctionIsMatch()
{
    QStringList methodNames;
    for(const auto& method : classMethods){
        methodNames.append(method.name());
    }
    QStringList infoNames;
    for(const auto& info : m_mappingInfos){
        infoNames.append (info.funName);
    }

    for(const auto& name : infoNames){
        if(!methodNames.contains(name)){
            IHttpControllerAbort::abortMappingMismatchFatal(QString("required function name: ").append(name), $ISourceLocation);
        }
    }
}

void IHttpControllerInfoDetail::checkMappingUrl()
{
    for(const MethodMappingInfo& info : m_mappingInfos){
        std::for_each(info.path.begin(), info.path.end(), [&](const QString& url){
            checkMappingUrlErrorCommon(url);
            CheckMappingUrlErrorWildCard(url);
        });
    }
}

void IHttpControllerInfoDetail::checkMappingUrlErrorCommon(const QString &url)
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
            IHttpControllerAbort::abortUrlInvalidCharacter(QString("url: ").append(url), $ISourceLocation);
        }

        if(piece == "." || piece == ".."){
            IHttpControllerAbort::abortUrlError(QString("url: ").append(url).append(" piece: ").append(piece), $ISourceLocation);
        }

        if(piece.contains(' ') || piece.contains('\t')){
            IHttpControllerAbort::abortUrlBlankCharacter(QString("url: ").append(url), $ISourceLocation);
        }
    }
}

void IHttpControllerInfoDetail::CheckMappingUrlErrorWildCard(const QString& url)
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


void IHttpControllerInfoDetail::checkMethod()
{
    using CheckFunType = void (IHttpControllerInfoDetail::*)(const IHttpControllerActionNode&);
    QList<CheckFunType> funs {
        &IHttpControllerInfoDetail::chechMethodSupportedReturnType,
        &IHttpControllerInfoDetail::checkMethodSupportedParamArgType,
        &IHttpControllerInfoDetail::checkMethodOfReturnVoid,
        &IHttpControllerInfoDetail::checkMethodBodyContentArgs,
        &IHttpControllerInfoDetail::checkMethodParamterWithSuffixProper,
    };

    for(auto& leaf : m_urlNodes){
        for(auto& fun : funs){
            std::mem_fn(fun)(this, leaf);
        }
    }
}

// TODO: json
void IHttpControllerInfoDetail::chechMethodSupportedReturnType(const IHttpControllerActionNode &node)
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
        auto errorInfo = info + "the error take place in Function : " + node.methodNode.functionName;
        qFatal(errorInfo.toUtf8());
    }

    if(validMetaType.contains(id)){
        return;
    }

    if(type.startsWith("I") && type.endsWith("Response")){
        return;
    }

    auto errorInfo = info + "the error take place in Function : " + node.methodNode.functionName;
    qFatal(errorInfo.toUtf8());
}

void IHttpControllerInfoDetail::checkMethodSupportedParamArgType(const IHttpControllerActionNode &node)
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

    const auto& typeNames = node.methodNode.parameterTypeNames;
    const auto& typeIds = node.methodNode.parameterTypeIds;
    const auto& count = node.methodNode.parameterCount;
    for(int i=0; i<count; i++) {
        QString typeName = typeNames[i];
        auto typeId = typeIds[i];

        if(typeId >= QMetaType::User){
            bool isSupportedType = isSpecialTypes(typeName) || IBeanTypeManage::instance()->isBeanIdExist(typeId) /*isBeanType(typeName)*/;
            if(!isSupportedType){
                IHttpControllerAbort::abortcontroller_check_param_Type_has_unsupported_user_defined_type( QString("At Function: ").append(node.methodNode.signature)
                                                                                                      .append(" At Param: ").append(typeName), $ISourceLocation);
            }
        } else{
            if(!allowType.contains(typeId)){
                IHttpControllerAbort::abortcontroller_check_param_Type_has_unsupported_inner_type(QString("At Function: ").append(node.methodNode.signature)
                                                                                              .append(" At Param: ").append(typeName), $ISourceLocation);
            }
        }
    }
}

void IHttpControllerInfoDetail::checkMethodOfReturnVoid(const IHttpControllerActionNode &node)
{
    if(node.methodNode.returnTypeId != QMetaType::Void){
        return;
    }

    const auto& typeNames = node.methodNode.parameterTypeNames;
    if(!typeNames.contains("IResponse") && !typeNames.contains("IResponse&")){
        QString info = "mapping function that return void should include IResponse in side function parameters\n"
                    "at Function : " + node.methodNode.functionName;
        qFatal(info.toUtf8());
    }
}

void IHttpControllerInfoDetail::checkMethodBodyContentArgs(const IHttpControllerActionNode &node)
{
    const auto& typeNames = node.methodNode.parameterTypeNames;
    auto index = typeNames.indexOf("QJsonValue&");
    if(index != -1){
        const auto& paramNames = node.methodNode.parameterNames;
        auto name = paramNames[index];
        if(!name.endsWith("_content")){
            QString info = "QJsonValue& can`t be used except in $Body expression\n"
                           "at Function : " + node.methodNode.functionName;
            qFatal(info.toUtf8());
        }
    }
}

void IHttpControllerInfoDetail::checkMethodParamterWithSuffixProper(const IHttpControllerActionNode &node)
{
    const auto& argNodes = node.methodNode.paramNodes;

    // get 中不能调用 body 的参数。
    if(node.httpMethod == IHttpMethod::GET){
        for(const IParameterNode& param : argNodes){
            if(param.name.endsWith("_body") || param.name.endsWith("_content")){
                IHttpControllerAbort::abortcontroller_method_get_but_want_body_content(QString("At Function: ").append(node.methodNode.signature).append(" Parameter: ").append(param.name), $ISourceLocation);
            }
        }
    }
}

bool IHttpControllerInfoDetail::isSpecialTypes(const QString &typeName)
{

    static const QStringList specialExternalTypes = {
        "IRequest",     "IRequest&",
        "IResponse",    "IResponse&",
        "IMultiPart",   "IMultiPart&",
        "ICookieJar",   "ICookieJar&",
        "ICookiePart",  "ICookiePart&"
        "ISessionJar",  "ISessionJar&",
        "IHeaderJar",   "IHeaderJar&",
        "IStringView"
    };

    return specialExternalTypes.contains(typeName);
}

// FIXME: check segment valid or not
QStringList IHttpControllerInfoDetail::parseRootPathArgs()
{
    static constexpr char CONTROLLER_MAPPING_FLAG[] = "IHttpControllerMapping$";
    QStringList ret;
    if(classInfo.contains(CONTROLLER_MAPPING_FLAG)){
        auto args =  classInfo[CONTROLLER_MAPPING_FLAG].split("/");
        for(const QString& arg : args){
            if(!arg.isEmpty()){
                ret.append(arg);
            }
        }
    }
    return ret;
}

QVector<IHttpControllerActionNode> IHttpControllerInfoDetail::createFunctionMappingLeaves(const MethodMappingInfo &mapping)
{
    QVector<IHttpControllerActionNode> ret;

    IHttpControllerActionNode node;
    auto funName = mapping.funName;
    node.httpMethod = mapping.method;
    QStringList pieces;
    for(const QMetaMethod& method : classMethods){
        if(method.name() == funName){
            node.methodNode = ISpawnUtil::construct<IMethodNode>(this->handler, this->className, method);
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

namespace ISpawnUtil
{
    template<>
    IHttpControllerInfo construct(void *handler, QString className, QMap<QString, QString> classInfo, QVector<QMetaMethod> methods)
    {
        IHttpControllerInfoDetail detail(handler, className, classInfo, methods);
        return detail;
    }
}

$PackageWebCoreEnd
