#include "IHttpControllerInfo.h"
#include "core/bean/IBeanTypeManage.h"
#include "core/util/ISpawnUtil.h"
#include "http/controller/IHttpControllerAbort.h"
#include "http/biscuits/IHttpMethod.h"
#include "http/controller/detail/IHttpControllerAction.h"

$PackageWebCoreBegin

struct IHttpMethodMappingInfo
{
    IHttpMethodMappingInfo(const QString& key, const QString& value, const QStringList&rootPath);
    QStringList normalizeUrlPiece(const QString& url, const QStringList& prefix);
    IMethodNode toMethodNode(void* handler, const QString& className, const QVector<QMetaMethod>& methods) const;
    QString toUrl() const;

    QString funName;
    QStringList path;
    IHttpMethod method;
    int index;
};

class IHttpControllerInfoDetail : public IHttpControllerInfo
{
public:
    IHttpControllerInfoDetail(void *handler, const QString &className,
                              const QMap<QString, QString> &classInfo,
                              const QVector<QMetaMethod> &methods);
private:
    void parseMapppingInfos();
    void parseMappingLeaves();

private:
    void checkUrlAndMethodMapping();
    void checkMappingOverloadFunctions();
    void checkMappingNameAndFunctionIsMatch();
    void checkMappingUrl();
    void checkMappingUrlErrorCommon(const QString& url);
    void CheckMappingUrlErrorWildCard(const QString& url);
    bool isPieceWildCard(const QString& piece);

private:
    void checkMethod();
    void chechMethodSupportedReturnType(const IHttpControllerAction& node);
    void checkMethodSupportedParamArgType(const IHttpControllerAction& node);
    void checkMethodOfReturnVoid(const IHttpControllerAction& node);
    void checkMethodBodyContentArgs(const IHttpControllerAction& node);
    void checkMethodParamterWithSuffixProper(const IHttpControllerAction& node);

private:
    bool isReturnTypeEmbeded(const IHttpControllerAction&);

private:
    bool isSpecialTypes(const QString&);

private:
    QStringList parseRootPaths();

private:
    QVector<IHttpMethodMappingInfo> m_mappingInfos;
};


IHttpMethodMappingInfo::IHttpMethodMappingInfo(const QString &key, const QString &value, const QStringList& rootPaths)
{
    auto args = key.split("$$$");
    if(args.length() != 4){
        qFatal("error");
    }

    this->index = args.last().toInt();
    args.pop_back();

    this->method = IHttpMethodUtil::toMethod(args.last());
    args.pop_back();

    this->funName = args.last();
    this->path = normalizeUrlPiece(value, rootPaths);
}

QStringList IHttpMethodMappingInfo::normalizeUrlPiece(const QString &url, const QStringList &rootPaths)
{
    QStringList ret = rootPaths;
    auto tempArgs = url.split("/");
    for(auto arg : tempArgs){
        arg = arg.trimmed();
        if(arg == "." || arg == ".."){
            IHttpControllerAbort::abortUrlDotAndDotDotError(url);
        }
        if(!arg.isEmpty()){
            ret.append(arg);
        }
    }
    return ret;
}

IMethodNode IHttpMethodMappingInfo::toMethodNode(void *handler, const QString &className, const QVector<QMetaMethod> &methods) const
{
    for(const QMetaMethod& method : methods){
        if(this->funName == method.name()){
            return ISpawnUtil::construct<IMethodNode>(handler, className, method);
        }
    }
    qFatal("this should always not be called");
    return {};
}

QString IHttpMethodMappingInfo::toUrl() const
{
    QStringList pieces;
    for(const QString& arg : this->path){
        if(arg.trimmed().isEmpty() || arg.trimmed() == "/"){
            continue;
        }
        pieces.append(arg.trimmed());
    }
    return pieces.join("/").prepend("/");
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
    static constexpr char CONTROLLER_INFO_PREFIX[] = "IHttpControllerFunMapping$$$";
    auto rootPaths = parseRootPaths();
    auto keys = classInfo.keys();
    for(auto key : keys){
        if(key.startsWith(CONTROLLER_INFO_PREFIX)){
            m_mappingInfos.append({key, classInfo[key], rootPaths});
        }
    }

    checkUrlAndMethodMapping();
}

void IHttpControllerInfoDetail::parseMappingLeaves()
{
    for(const auto& mapping : m_mappingInfos){
        IHttpControllerAction node;
        node.httpMethod = mapping.method;
        node.url = mapping.toUrl();
        node.methodNode = mapping.toMethodNode(this, this->className, this->classMethods);
        m_urlNodes.append(node);
    }

    checkMethod();
}

void IHttpControllerInfoDetail::checkUrlAndMethodMapping()
{
    checkMappingOverloadFunctions();
    checkMappingNameAndFunctionIsMatch();
    checkMappingUrl();
}

void IHttpControllerInfoDetail::checkMappingOverloadFunctions()
{
    QSet<QString> usedMethods;
    for(const IHttpMethodMappingInfo& info : m_mappingInfos){
        usedMethods.insert(info.funName);
    }

    QStringList names;
    for(const auto& method : classMethods){
        if(usedMethods.contains(method.name())){
            if(names.contains(method.name())){
                IHttpControllerAbort::abortOverloadOrDefaultValueFunctionNotSupported(QString("duplicated overloaded function name: ").append(method.name()));
            }
            names.append(method.name());
        }
    }
}

void IHttpControllerInfoDetail::checkMappingNameAndFunctionIsMatch()
{
    QSet<QString> infoNames;
    for(const auto& info : m_mappingInfos){
        infoNames.insert(info.funName);
    }

    QSet<QString> methodNames;
    for(const auto& method : classMethods){
        methodNames.insert(method.name());
    }

    for(const auto& name : infoNames){
        if(!methodNames.contains(name)){
            IHttpControllerAbort::abortMappingMismatchFatal(
                        QString("required function name: ").append(name), $ISourceLocation);
        }
    }
}

void IHttpControllerInfoDetail::checkMappingUrl()
{
    for(const IHttpMethodMappingInfo& info : m_mappingInfos){
        std::for_each(info.path.begin(), info.path.end(), [&](const QString& piece){
            if(piece.isEmpty()){
                return;
            }
            if(isPieceWildCard(piece)){
                CheckMappingUrlErrorWildCard(piece);
            }else{
                checkMappingUrlErrorCommon(piece);
            }
        });
    }
}

void IHttpControllerInfoDetail::checkMappingUrlErrorCommon(const QString &piece)
{
//    static QRegularExpression urlPieceReg("^[0-9a-zA-Z\\$\\.\\+\\*\\(\\)\\,!_\\$']+$");    // TODO: I don`t know whether it right or not see: https://www.cnblogs.com/cxygg/p/9278542.html
//    static QRegularExpression regexInclude(R"([a-zA-Z0-9\-_.]+|%(?:[0-9a-fA-F]{2})+)");
    static QRegularExpression regexExclude(R"([^ \t\n\r\f\v~`!@#$%^&*()+=|\[\]{}\'\";:/?,.<>]+)");
    // 允许字母（大小写）、数字、连字符、下划线、点号、问号、等号、与号、斜杠、逗号、分号、冒号、破折号、波浪线、井号、星号、加号、方括号、圆括号、竖线、反斜杠、竖线、单引号、双引号、尖括号、美元符号、感叹号、at 符号以及百分号编码（%XX 形式）
    static QRegularExpression regexInclude(R"([a-zA-Z0-9\-\._\?\=\&\|/,\:;\'\"\-\~\#\*\+\[\]\(\)\|\$\!\@]+|%(?:[0-9a-fA-F]{2})+)");

    if(!regexExclude.match(piece).hasMatch() || !regexInclude.match(piece).hasMatch()){
        IHttpControllerAbort::abortUrlInvalidCharacter(QString("url: ").append(piece), $ISourceLocation);
    }
}

void IHttpControllerInfoDetail::CheckMappingUrlErrorWildCard(const QString& piece)
{
    static QRegularExpression validName("^[0-9a-zA-Z_]+$");
    static QRegularExpression expression0("^<(.*)>$");
    static QRegularExpression expression1("^<(.*):(.*)>$");
    static QRegularExpression expression2("^<(reg)?:(.*):(.*)>$");

    if(!(piece.startsWith('<') && piece.endsWith('>'))){
        return;
    }

    int colonCount = piece.count(':');
    if(colonCount == 0){
        auto result = expression0.match(piece);
        if(result.hasMatch()){
            auto name = result.captured(1);
            if(!validName.match(name).isValid()){
                QString info = "not a valid name in wideCard expression:\n\t" + piece;
                qFatal(info.toUtf8());
            }
        }
    } else if(colonCount == 1){
        auto result = expression1.match(piece);
        auto name = result.captured(1);
        auto validator = result.captured(2);
        if(!validName.match(name).isValid() || !validName.match(validator).isValid()){
            QString info = "not a valid name or validator name in wideCard expression:\n\t" + piece;
            qFatal(info.toUtf8());
        }
    } else if(colonCount == 2){
        auto result = expression2.match(piece);
        if(!result.hasMatch()){
            QString info = "not a valid regexpression wideCard expression:\n\t" + piece;
            qFatal(info.toUtf8());
        }
        auto name = result.captured(2);
        auto regexp = result.captured(3);
        if(!validName.match(name).isValid()){
            QString info = "not a valid name in wideCard expression:\n\t" + piece;
            qFatal(info.toUtf8());
        }
        QRegularExpression exp(regexp);
        if(!exp.isValid()){
            QString info = "not a valid regexp in wideCard expression:\n\t" + piece;
            qFatal(info.toUtf8());
        }
    }else {
        QString info = "wideCard do not supoort for expression more than two conos: \n\t" + piece;
        qFatal(info.toUtf8());
    }

}

bool IHttpControllerInfoDetail::isPieceWildCard(const QString &piece)
{
    static QRegularExpression wildcard("^<.*>$");
    return wildcard.match(piece).hasMatch();
}


void IHttpControllerInfoDetail::checkMethod()
{
    using CheckFunType = void (IHttpControllerInfoDetail::*)(const IHttpControllerAction&);
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
void IHttpControllerInfoDetail::chechMethodSupportedReturnType(const IHttpControllerAction &node)
{
    const static QString info = "this kind of return type not supported, please change the return type!";

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

    if(validMetaType.contains(id)){
        return;
    }

    if(IBeanTypeManage::instance()->isBeanIdExist(id)){
        return;
    }

    if(type.startsWith("I") && type.endsWith("Response")){
        return;
    }

    if(id == QMetaType::UnknownType){
        auto errorInfo = info + "the error take place in Function : " + node.methodNode.functionName;
        qFatal(errorInfo.toUtf8());
    }

    auto errorInfo = info + "the error take place in Function : " + node.methodNode.functionName;
    qFatal(errorInfo.toUtf8());
}

void IHttpControllerInfoDetail::checkMethodSupportedParamArgType(const IHttpControllerAction &node)
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

void IHttpControllerInfoDetail::checkMethodOfReturnVoid(const IHttpControllerAction &node)
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

void IHttpControllerInfoDetail::checkMethodBodyContentArgs(const IHttpControllerAction &node)
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

void IHttpControllerInfoDetail::checkMethodParamterWithSuffixProper(const IHttpControllerAction &node)
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

QStringList IHttpControllerInfoDetail::parseRootPaths()
{
    static constexpr char CONTROLLER_MAPPING_FLAG[] = "IHttpControllerMapping$";
    QStringList ret;
    if(classInfo.contains(CONTROLLER_MAPPING_FLAG) && !classInfo[CONTROLLER_MAPPING_FLAG].isEmpty()){
        auto args =  classInfo[CONTROLLER_MAPPING_FLAG].split("/");
        for(const QString& arg : args){
            auto piece = arg.trimmed();
            if(piece == "." || piece == ".."){
                IHttpControllerAbort::abortUrlDotAndDotDotError("Controller mapping:" + classInfo[CONTROLLER_MAPPING_FLAG]);
            }
            if(!piece.isEmpty()){
                ret.append(piece);
            }
        }
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
