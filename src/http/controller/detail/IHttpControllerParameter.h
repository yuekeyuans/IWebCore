#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/unit/ISingletonUnit.h"
#include "core/task/default/IInitializationTaskInterface.h"
#include "http/response/IResponseWare.h"

$PackageWebCoreBegin

// TODO: 废弃这个东西
class IRequest;
class IResponse;
struct IMethodNode;
struct IArgumentType;
class IHttpControllerParameter  : public IInitializationTaskInterface<IHttpControllerParameter>
{
public:
    using ParamType = void*[11];
    using CreateParamFunType = void*(IHttpControllerParameter::*)(const IArgumentType& node, IRequest& request, bool& ok);
    using ReleaseParamFunType = bool (IHttpControllerParameter::*)(const IArgumentType& node, void *obj);

public:
    IHttpControllerParameter() = default;

public:
    static bool createArguments(const IMethodNode& methodNode, ParamType& params, IRequest& request);
    static void destroyArguments(const IMethodNode& node, void **params);
    static void resolveReturnValue(IResponse& response, const IMethodNode& functionNode, void* ptr);

private:
    void *createReturnParam(int paramTypeId);
    void *createArgParam(const IArgumentType&node, IRequest& request, bool& ok);
    void destroyReturnParam(void *obj, int paramTypeId);
    void destroyArgParam(const IArgumentType& node, void *obj);

private:
    void* getParamOfSystem(const IArgumentType& node, IRequest& request, bool& ok);
    void* getParamOfMultipart(const IArgumentType& node, IRequest& request, bool& ok);
    void* getParamOfCookiePart(const IArgumentType& node, IRequest& request, bool& ok);
    void* getParamOfSession(const IArgumentType& node, IRequest& request, bool& ok);
    void* getParamOfBean(const IArgumentType& node, IRequest& request, bool& ok);
    void* getParamOfJsonType(const IArgumentType& node, IRequest& request, bool& ok);
    void* getParamOfPrimitiveType(const IArgumentType& node, IRequest& request, bool& ok);
    void* getParamOfStringType(const IArgumentType& node, IRequest& request, bool& ok);

    bool releaseParamOfSystem(const IArgumentType& node, void *obj);
    bool releaseParamOfMultipart(const IArgumentType& node, void *obj);
    bool releaseParamOfCookiePart(const IArgumentType& node, void *obj);
    bool releaseParamOfBean(const IArgumentType& node, void *obj);
    bool releaseParamOfJsonType(const IArgumentType& node, void *obj);
    bool releaseParamOfPrimitiveType(const IArgumentType& node, void *obj);
    bool releaseParamOfStringType(const IArgumentType& node, void *obj);

private:
    void wrapVoidReturnInstance(IResponse& response, const IMethodNode& functionNode, ParamType &params);
    QSharedPointer<IResponseWare> createStringReturnInstance(void** params);
    QSharedPointer<IResponseWare> createInterfaceReturnInstance(void** params);

private:
    void initSystemTypes();
    void initMultiPartTypes();
    void initCookiePartTypes();
    void initPrimitiveTypes();
    void initBeanTypes();

private:
    virtual void $task() final;

private:
    QVector<int> m_systemTypes;
    QVector<int> m_multiPartTypes;
    QVector<int> m_cookiePartTypes;
    QVector<int> m_beanTypes;
    QVector<int> m_primitiveTypes;
    QVector<int> m_jsonTypes;
    QVector<int> m_stringTypes;
    QVector<QVector<int>> m_judgeTypes;
};

$PackageWebCoreEnd
