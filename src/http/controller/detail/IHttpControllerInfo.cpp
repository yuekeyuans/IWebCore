//#include "IHttpControllerInfo.h"
//#include "core/bean/IBeanTypeManage.h"
//#include "core/util/ISpawnUtil.h"
//#include "core/util/IHeaderUtil.h"
//#include "http/biscuits/IHttpMethod.h"
//#include "http/controller/IHttpControllerAbort.h"
//#include "http/controller/IHttpControllerAction.h"
//#include "http/controller/detail/IHttpUrlFragment.h"

//$PackageWebCoreBegin

//struct IHttpMethodMappingInfo
//{
//public:
//    IHttpMethodMappingInfo(const QString& key);

//public:
//    int index;
//    QString funName;
//    std::vector<IHttpUrlFragment> fragments;
//    IHttpMethod method;
//};

//class IHttpControllerInfoDetail
//{
//public:
//    IHttpControllerInfoDetail(void *handler, const QString &className,
//                              const QMap<QString, QString> &classInfo,
//                              const QVector<QMetaMethod> &methods);
//private:
//    void parseMapppingInfos();
//    void parseMappingLeaves();
//    void parseRootPaths();

//private:
//    std::vector<IHttpUrlFragment> parseFragments(const QString& path);
//    IMethodNode getHttpMethodNode(const QString& name);

//private:
//    void checkMappingOverloadFunctions();
//    void checkMappingNameAndFunctionIsMatch();

//private:
//    void* handler{};
//    QString className;
//    QMap<QString, QString> classInfo;
//    QVector<QMetaMethod> classMethods;

//private:
//    std::vector<IHttpUrlFragment> rootFragments;

//public:
//    QVector<IHttpControllerAction> m_urlNodes;

//private:
//    QVector<IHttpMethodMappingInfo> m_mappingInfos;
//};


//IHttpMethodMappingInfo::IHttpMethodMappingInfo(const QString &key/*, const QString &value, const QStringList& rootPaths*/)
//{
//    auto args = key.split("$$$");
//    if(args.length() != 4){
//        qFatal("error");
//    }

//    this->index = args.last().toInt();
//    args.pop_back();

//    this->method = IHttpMethodUtil::toMethod(args.last());
//    args.pop_back();

//    this->funName = args.last();
//}

//IHttpControllerInfoDetail::IHttpControllerInfoDetail(void *handler_, const QString &className_, const QMap<QString, QString> &classInfo_, const QVector<QMetaMethod> &methods_)
//{
//    this->handler = handler_;
//    this->className = className_;
//    this->classInfo = classInfo_;
//    this->classMethods = methods_;

//    parseRootPaths();
//    parseMapppingInfos();
//    parseMappingLeaves();
//}

//void IHttpControllerInfoDetail::parseMapppingInfos()
//{
//    static constexpr char CONTROLLER_INFO_PREFIX[] = "IHttpControllerFunMapping$$$";
//    auto keys = classInfo.keys();
//    for(auto key : keys){
//        if(key.startsWith(CONTROLLER_INFO_PREFIX)){
//            IHttpMethodMappingInfo info(key);
//            info.fragments = rootFragments;
//            auto fragments = parseFragments(classInfo[key]);
//            info.fragments.insert(info.fragments.end(), fragments.begin(), fragments.end());

//            m_mappingInfos.append(info);
//        }
//    }

//    checkMappingOverloadFunctions();
//    checkMappingNameAndFunctionIsMatch();
//}

//void IHttpControllerInfoDetail::parseMappingLeaves()
//{
//    for(const IHttpMethodMappingInfo& mapping : m_mappingInfos){
//        IHttpControllerAction node;
//        node.httpMethod = mapping.method;
//        node.route = ISpawnUtil::construct<IHttpUrl>(mapping.fragments);
//        node.methodNode = getHttpMethodNode(mapping.funName);
//        m_urlNodes.append(node);
//    }
//}

//void IHttpControllerInfoDetail::checkMappingOverloadFunctions()
//{
//    QSet<QString> usedMethods;
//    for(const IHttpMethodMappingInfo& info : m_mappingInfos){
//        usedMethods.insert(info.funName);
//    }

//    QStringList names;
//    for(const auto& method : classMethods){
//        if(usedMethods.contains(method.name())){
//            if(names.contains(method.name())){
//                IHttpControllerAbort::abortOverloadOrDefaultValueFunctionNotSupported(QString("duplicated overloaded function name: ").append(method.name()));
//            }
//            names.append(method.name());
//        }
//    }
//}

//void IHttpControllerInfoDetail::checkMappingNameAndFunctionIsMatch()
//{
//    QSet<QString> infoNames;
//    for(const auto& info : m_mappingInfos){
//        infoNames.insert(info.funName);
//    }

//    QSet<QString> methodNames;
//    for(const auto& method : classMethods){
//        methodNames.insert(method.name());
//    }

//    for(const auto& name : infoNames){
//        if(!methodNames.contains(name)){
//            IHttpControllerAbort::abortMappingMismatchFatal(
//                        QString("required function name: ").append(name), $ISourceLocation);
//        }
//    }
//}

//void IHttpControllerInfoDetail::parseRootPaths()
//{
//    static constexpr char CONTROLLER_MAPPING_FLAG[] = "IHttpControllerMapping$";
//    if(classInfo.contains(CONTROLLER_MAPPING_FLAG) && !classInfo[CONTROLLER_MAPPING_FLAG].isEmpty()){
//        rootFragments = parseFragments(classInfo[CONTROLLER_MAPPING_FLAG]);
//    }
//}

//std::vector<IHttpUrlFragment> IHttpControllerInfoDetail::parseFragments(const QString &path)
//{
//    static constexpr char CONTROLLER_MAPPING_FLAG[] = "IHttpControllerMapping$";
//    std::vector<IHttpUrlFragment> ret;
//    auto args =  path.split("/");
//    for(const QString& arg : args){
//        auto piece = arg.trimmed();
//        if(piece == "." || piece == ".."){
//            IHttpControllerAbort::abortUrlDotAndDotDotError("Controller mapping:" + classInfo[CONTROLLER_MAPPING_FLAG]);
//        }
//        if(!piece.isEmpty()){
//            ret.push_back(ISpawnUtil::construct<IHttpUrlFragment>(piece));
//        }
//    }
//    return ret;
//}

//IMethodNode IHttpControllerInfoDetail::getHttpMethodNode(const QString &name)
//{
//    for(const QMetaMethod& method : classMethods){
//        if(name == method.name()){
//            return ISpawnUtil::construct<IMethodNode>(handler, className, method);
//        }
//    }
//    qFatal("this will never be called");
//    return {};
//}

//namespace ISpawnUtil
//{
//    template<>
//    QVector<IHttpControllerAction> construct(void *handler, QString className, QMap<QString, QString> classInfo, QVector<QMetaMethod> methods)
//    {
//        IHttpControllerInfoDetail detail(handler, className, classInfo, methods);
//        return detail.m_urlNodes;
//    }
//}

//$PackageWebCoreEnd
