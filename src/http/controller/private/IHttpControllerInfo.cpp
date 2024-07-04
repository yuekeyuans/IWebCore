#include "IHttpControllerInfo.h"
#include "core/bean/IBeanTypeManage.h"
#include "core/util/ISpawnUtil.h"
#include "http/controller/IControllerAbort.h"
#include "http/biscuits/IHttpMethod.h"
#include "http/base/IUrlActionNode.h"

$PackageWebCoreBegin

class IHttpControllerInfoDetail : public IHttpControllerInfo
{
    struct MappingInfo
    {
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
    void checkUrlMappings();
    void checkMappingOverloadFunctions();
    void checkMappingNameAndFunctionIsMatch();
    void checkMappingUrlIsValid();
    void checkMappingMethodArgsIsValid();

private:
    void chekcUrlErrorCommon(const QString& url);
    void CheckUrlErrorWildCard(const QString& url);
    void chechMethodSupportedReturnType(const IUrlActionNode& node);
    void checkMethodSupportedParamArgType(const IUrlActionNode& node);
    void checkMethodOfReturnVoid(const IUrlActionNode& node);
    void checkMethodBodyContentArgs(const IUrlActionNode& node);
    void checkMethodParamterWithSuffixProper(const IUrlActionNode& node);


private:
    QStringList toNormalUrl(const QString& url, const QStringList& prefix);
    bool isBeanType(const QString&);
    bool isSpecialTypes(const QString&);



private:
    void parseRootPathArgs();
    void parseMapppingInfos();
    QVector<IUrlActionNode> createFunctionMappingLeaves(const MappingInfo& mapping);
    QVector<IUrlActionNode> createMappingLeaves();

private:
    QStringList m_rootPathArgs;
    QVector<MappingInfo> m_mappingInfos;
};

inline IHttpControllerInfoDetail::IHttpControllerInfoDetail(void *handler_, const QString &className_, const QMap<QString, QString> &classInfo_, const QVector<QMetaMethod> &methods_)
{
    this->handler = handler_;
    this->className = className_;
    this->classInfo = classInfo_;
    this->classMethods = methods_;
    parseRootPathArgs();
    parseMapppingInfos();

    checkUrlMappings();

    m_urlNodes = createMappingLeaves();
}

inline void IHttpControllerInfoDetail::checkUrlMappings()
{
    checkMappingOverloadFunctions();
    checkMappingNameAndFunctionIsMatch();
    checkMappingUrlIsValid();
    checkMappingMethodArgsIsValid();
}

void IHttpControllerInfoDetail::checkMappingOverloadFunctions()
{
    QStringList names;
    for(const auto& method : classMethods){
        if(names.contains(method.name())){
            IControllerAbort::abortOverloadOrDefaultValueFunctionNotSupported(QString("name: ").append(method.name()), $ISourceLocation);
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
            IControllerAbort::abortMappingMismatchFatal(QString("name: ").append(name), $ISourceLocation);
        }
    }
}

void IHttpControllerInfoDetail::checkMappingUrlIsValid()
{
    for(const MappingInfo& info : m_mappingInfos){
        std::for_each(info.path.begin(), info.path.end(), [&](const QString& url){
            chekcUrlErrorCommon(url);
            CheckUrlErrorWildCard(url);
        });
    }
}

void IHttpControllerInfoDetail::checkMappingMethodArgsIsValid()
{
    using CheckFunType = void (IHttpControllerInfoDetail::*)(const IUrlActionNode&);
    QList<CheckFunType> funs {
        &IHttpControllerInfoDetail::chechMethodSupportedReturnType,
        &IHttpControllerInfoDetail::checkMethodSupportedParamArgType,
//        checkMethodArgNameIntegrality,
        &IHttpControllerInfoDetail::checkMethodOfReturnVoid,
        &IHttpControllerInfoDetail::checkMethodBodyContentArgs,
        &IHttpControllerInfoDetail::checkMethodParamterWithSuffixProper,
//        checkMethodParamterWithSuffixSet,
    };

    auto leaves = createMappingLeaves();
    for(auto& leaf : leaves){
        for(auto& fun : funs){
            std::mem_fn(fun)(this, leaf);
        }
    }
}

void IHttpControllerInfoDetail::chekcUrlErrorCommon(const QString &url)
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
            IControllerAbort::abortUrlInvalidCharacter(QString("url: ").append(url), $ISourceLocation);
        }

        if(piece == "." || piece == ".."){
            IControllerAbort::abortUrlError(QString("url: ").append(url).append(" piece: ").append(piece), $ISourceLocation);
        }

        if(piece.contains(' ') || piece.contains('\t')){
            IControllerAbort::abortUrlBlankCharacter(QString("url: ").append(url), $ISourceLocation);
        }
    }
}

void IHttpControllerInfoDetail::CheckUrlErrorWildCard(const QString& url)
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

void IHttpControllerInfoDetail::chechMethodSupportedReturnType(const IUrlActionNode &node)
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

void IHttpControllerInfoDetail::checkMethodSupportedParamArgType(const IUrlActionNode &node)
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
            bool isSupportedType = isSpecialTypes(typeName) || isBeanType(typeName);
            if(!isSupportedType){
                IControllerAbort::abortcontroller_check_param_Type_has_unsupported_user_defined_type( QString("At Function: ").append(node.methodNode.expression)
                                                                                                      .append(" At Param: ").append(typeName), $ISourceLocation);
            }
        } else{
            if(!allowType.contains(typeId)){
                IControllerAbort::abortcontroller_check_param_Type_has_unsupported_inner_type(QString("At Function: ").append(node.methodNode.expression)
                                                                                              .append(" At Param: ").append(typeName), $ISourceLocation);
            }
        }
    }
}

void IHttpControllerInfoDetail::checkMethodOfReturnVoid(const IUrlActionNode &node)
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

void IHttpControllerInfoDetail::checkMethodBodyContentArgs(const IUrlActionNode &node)
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

void IHttpControllerInfoDetail::checkMethodParamterWithSuffixProper(const IUrlActionNode &node)
{
    const auto& argNodes = node.methodNode.paramNodes;

    // get 中不能调用 body 的参数。
    if(node.httpMethod == IHttpMethod::GET){
        for(const auto& param : argNodes){
            if(param.paramName.endsWith("_body") || param.paramName.endsWith("_content")){
                IControllerAbort::abortcontroller_method_get_but_want_body_content(QString("At Function: ").append(node.methodNode.expression).append(" Parameter: ").append(param.paramName), $ISourceLocation);
            }
        }
    }
}

QStringList IHttpControllerInfoDetail::toNormalUrl(const QString &url, const QStringList &prefix)
{
    QStringList ret = prefix;
    auto tempArgs = url.split("/");
    for(auto arg : tempArgs){
        arg = arg.trimmed();
        if(arg == "." || arg == ".."){
            IControllerAbort::abortUrlError($ISourceLocation);
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

bool IHttpControllerInfoDetail::isBeanType(const QString &typeName)
{
    return IBeanTypeManage::containBean(typeName);
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

void IHttpControllerInfoDetail::parseRootPathArgs()
{
    static constexpr char CONTROLLER_MAPPING_FLAG[] = "IHttpControllerMapping$";
    QStringList rootPathArgs;
    if(classInfo.contains(CONTROLLER_MAPPING_FLAG)){
        rootPathArgs =  classInfo[CONTROLLER_MAPPING_FLAG].split("/");
    }
}

void IHttpControllerInfoDetail::parseMapppingInfos()
{
    static constexpr char CONTROLLER_INFO_PREFIX[] = "IHttpControllerFunMapping$";
    auto keys = classInfo.keys();
    for(auto key : keys){
        if(key.startsWith(CONTROLLER_INFO_PREFIX)){
            QStringList args = key.split("$");
            MappingInfo info{
                args[1],
                toNormalUrl(classInfo[key], m_rootPathArgs),
                IHttpMethodUtil::toMethod(args[2]),
                args[3].toInt()
            };

            m_mappingInfos.append(info);
        }
    }
}

QVector<IUrlActionNode> IHttpControllerInfoDetail::createFunctionMappingLeaves(const MappingInfo &mapping)
{
    QVector<IUrlActionNode> ret;

    IUrlActionNode node;
    auto funName = mapping.funName;
    node.httpMethod = mapping.method;
    QStringList pieces;
    for(const auto& method : classMethods){
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

QVector<IUrlActionNode> IHttpControllerInfoDetail::createMappingLeaves()
{
    QVector<IUrlActionNode> ret;
    for(const auto& arg : m_mappingInfos){
        ret.append(createFunctionMappingLeaves(arg));
    }
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
