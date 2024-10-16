﻿#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/unit/ISingletonUnit.h"
#include "core/task/default/IInitializationTaskInterface.h"
#include "http/response/IResponseWare.h"

$PackageWebCoreBegin

class IRequest;
class IResponse;
struct IMethodNode;
struct IParameterNode;
class IHttpControllerParameter  : public IInitializationTaskInterface<IHttpControllerParameter>
{
public:
    using ParamType = void*[11];
    using CreateParamFunType = void*(IHttpControllerParameter::*)(const IParameterNode& node, IRequest& request, bool& ok);
    using ReleaseParamFunType = bool (IHttpControllerParameter::*)(const IParameterNode& node, void *obj);

public:
    IHttpControllerParameter() = default;

public:
    static bool createArguments(const IMethodNode& methodNode, ParamType& params, IRequest& request);
    static void destroyArguments(const IMethodNode& node, void **params);
    static void resolveReturnValue(IResponse& response, const IMethodNode& functionNode, ParamType &params);

private:
    void *createReturnParam(int paramTypeId);
    void *createArgParam(const IParameterNode&node, IRequest& request, bool& ok);
    void destroyReturnParam(void *obj, int paramTypeId);
    void destroyArgParam(const IParameterNode& node, void *obj);

private:
    void* getParamOfSystem(const IParameterNode& node, IRequest& request, bool& ok);
    void* getParamOfMultipart(const IParameterNode& node, IRequest& request, bool& ok);
    void* getParamOfCookiePart(const IParameterNode& node, IRequest& request, bool& ok);
    void* getParamOfSession(const IParameterNode& node, IRequest& request, bool& ok);
    void* getParamOfBean(const IParameterNode& node, IRequest& request, bool& ok);
    void* getParamOfJsonType(const IParameterNode& node, IRequest& request, bool& ok);
    void* getParamOfPrimitiveType(const IParameterNode& node, IRequest& request, bool& ok);
    void* getParamOfStringType(const IParameterNode& node, IRequest& request, bool& ok);

    bool releaseParamOfSystem(const IParameterNode& node, void *obj);
    bool releaseParamOfMultipart(const IParameterNode& node, void *obj);
    bool releaseParamOfCookiePart(const IParameterNode& node, void *obj);
    bool releaseParamOfBean(const IParameterNode& node, void *obj);
    bool releaseParamOfJsonType(const IParameterNode& node, void *obj);
    bool releaseParamOfPrimitiveType(const IParameterNode& node, void *obj);
    bool releaseParamOfStringType(const IParameterNode& node, void *obj);

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
