#pragma once

#include "core/base/IHeaderUtil.h"
#include "http/jar/IMultiPart.h"

$PackageWebCoreBegin

class IBeanWare;
class IRequest;
class IResponse;

struct IParamNode;

// 由于 bean 的装配比较复杂，代码再这里单写一份
class IHttpControllerBeanParameter
{
public:
    using ParamFun = void*(*)(IBeanWare*, IRequest&);

public:
    IHttpControllerBeanParameter() = default;

    static void* getParamOfBean(const IParamNode& node, IRequest &request);

private:
    static void* assamleBeanWareWithContent(IBeanWare* bean, IRequest& request);
    static void* assambleBeanWareWithBody(IBeanWare* bean, IRequest& request);
    static void* assambleBeanWareWithParameter(IBeanWare* bean, IRequest& request);
    static void* assambleBeanWareWithUrl(IBeanWare* bean, IRequest& request);
    static void* assambleBeanWareWithHeaders(IBeanWare* bean, IRequest& request);
    static void* assambleBeanWareWithMixed(IBeanWare* bean, IRequest& request);

    static void* assambleBeanWareWithCookie(IBeanWare* bean, IRequest& request);
    static void* assambleBeanWareWithSession(IBeanWare* bean, IRequest& request);
    static void* assambleBeanWareWithApplication(IBeanWare* bean, IRequest& request);
    static void* assambleBeanWareWithSystem(IBeanWare* bean, IRequest& request);

private:
    static void* resolveBodyForm(IBeanWare* bean, IRequest& request);
    static void* resolveBodyMultiPart(IBeanWare* bean, IRequest& request);
    static void* resolveBodyJson(IBeanWare* bean, IRequest& request);
    static void* resolveBodyXml(IBeanWare* bean, IRequest& request);

    static QMap<QString, QVariant> resolveBeanFieldAsMap(const QList<QPair<QString, QString>>& list, IBeanWare* bean, IRequest&request, bool& ok);
    static QMap<QString, QVariant> resolveBeanFieldAsMap(const QMap<QString, QString>& map, IBeanWare* bean, IRequest& request, bool& ok);
    static QMap<QString, QVariant> resolveBeanFieldAsMap(const QVector<IMultiPart>& parts, IBeanWare* bean, IRequest& request, bool& ok);
    static QMap<QString, QVariant> resolveBeanFieldAsMap(const QMultiHash<QString, QString>& parts, IBeanWare* bean, IRequest& request, bool& ok);

    static bool checkKeyInJsonAndBean(const QJsonObject& obj, IBeanWare* bean, IRequest& request);
    static bool checkKeyInMultiPart(const QVector<IMultiPart> &parts, IBeanWare* bean, IRequest& request);
    static bool checkKeyInQByteArrayMap(const QMap<QString, QString>& map, IBeanWare* bean, IRequest& request);
    static bool checkKeyInListPair(const QMultiHash<QString, QString>& list, IBeanWare* bean, IRequest& request);
    static bool checkKeyInQStringMap(const QMap<QString, QString>& map, IBeanWare* bean, IRequest& request);

    // 获取 bean 处理方式， 是否是 strict 方式
    static bool isBeanResoveStrictMode();

    static QStringList& getParameterSuffix();
    static QVector<ParamFun>& getParameterFun();
};

$PackageWebCoreEnd
