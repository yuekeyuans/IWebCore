#include "IHttpControllerInfo.h"
#include "core/bean/IBeanTypeManage.h"
#include "core/util/ISpawnUtil.h"
#include "core/util/IHeaderUtil.h"
#include "http/biscuits/IHttpMethod.h"
#include "http/controller/IHttpControllerAbort.h"
#include "http/controller/IHttpControllerAction.h"

$PackageWebCoreBegin
$PackageDetailBegin

struct IHttpMethodMappingInfo
{
public:
    IHttpMethodMappingInfo(const QString& key, const QString& value, const QStringList&rootPath);
    QStringList normalizeUrlPiece(const QString& url, const QStringList& prefix);
    IMethodNode toMethodNode(void* handler, const QString& className, const QVector<QMetaMethod>& methods) const;

public:
    QString funName;
    QStringList path;
    IHttpMethod method;
    int index;
};

class IHttpControllerInfoDetail //: public IHttpControllerInfo
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

private:
    QStringList parseRootPaths();

private:
    void* handler{};
    QString className;
    QMap<QString, QString> classInfo;
    QVector<QMetaMethod> classMethods;

public:
    QVector<IHttpControllerAction> m_urlNodes;

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
    for(const IHttpMethodMappingInfo& mapping : m_mappingInfos){
        IHttpControllerAction node;
        node.httpMethod = mapping.method;
        node.route = ISpawnUtil::construct<IHttpUrl>(mapping.path);
        node.methodNode = mapping.toMethodNode(this, this->className, this->classMethods);

        m_urlNodes.append(node);
    }
}

void IHttpControllerInfoDetail::checkUrlAndMethodMapping()
{
    checkMappingOverloadFunctions();
    checkMappingNameAndFunctionIsMatch();
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

$PackageDetailEnd
$PackageWebCoreEnd

$PackageWebCoreBegin

namespace ISpawnUtil
{
    template<>
    QVector<IHttpControllerAction> construct(void *handler, QString className, QMap<QString, QString> classInfo, QVector<QMetaMethod> methods)
    {
        detail::IHttpControllerInfoDetail detail(handler, className, classInfo, methods);
        return detail.m_urlNodes;
    }
}

$PackageWebCoreEnd
