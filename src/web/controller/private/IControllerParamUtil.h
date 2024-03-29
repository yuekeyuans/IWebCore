﻿#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/unit/ISingletonUnit.h"
#include "web/response/IResponseWare.h"

$PackageWebCoreBegin

class IRequest;
class IResponse;
struct IMethodNode;
struct IFunctionNode;
struct IParamNode;

class IControllerParamUtil  : public ISingletonUnit<IControllerParamUtil>// : public IInitializationTaskUnit<IControllerParamUtil>
{
public:
    using ParamType = void*[11];
    using CreateParamFunType = void*(*)(const IParamNode& node, IRequest& request, bool& ok);
    using ReleaseParamFunType = bool (*)(const IParamNode& node, void *obj);

public:
    IControllerParamUtil() = default;

public:
    static bool createArguments(const IMethodNode& methodNode, ParamType& params, IRequest& request);
    static void destroyArguments(const IMethodNode& node, void **params);
    static void resolveReturnValue(IResponse& response, const IMethodNode& functionNode, ParamType &params);

private:
    static void *createReturnParam(int paramTypeId);
    static void *createArgParam(const IParamNode&node, IRequest& request, bool& ok);
    static void destroyReturnParam(void *obj, int paramTypeId);
    static void destroyArgParam(const IParamNode& node, void *obj);

private:
    static void* getParamOfSystem(const IParamNode& node, IRequest& request, bool& ok);
    static void* getParamOfMultipart(const IParamNode& node, IRequest& request, bool& ok);
    static void* getParamOfCookiePart(const IParamNode& node, IRequest& request, bool& ok);
    static void* getParamOfSession(const IParamNode& node, IRequest& request, bool& ok);
    static void* getParamOfBean(const IParamNode& node, IRequest& request, bool& ok);
    static void* getParamOfJsonType(const IParamNode& node, IRequest& request, bool& ok);
    static void* getParamOfPrimitiveType(const IParamNode& node, IRequest& request, bool& ok);
    static void* getParamOfStringType(const IParamNode& node, IRequest& request, bool& ok);

    static bool releaseParamOfSystem(const IParamNode& node, void *obj);
    static bool releaseParamOfMultipart(const IParamNode& node, void *obj);
    static bool releaseParamOfCookiePart(const IParamNode& node, void *obj);
    static bool releaseParamOfBean(const IParamNode& node, void *obj);
    static bool releaseParamOfJsonType(const IParamNode& node, void *obj);
    static bool releaseParamOfPrimitiveType(const IParamNode& node, void *obj);
    static bool releaseParamOfStringType(const IParamNode& node, void *obj);

private:
    static void wrapVoidReturnInstance(IResponse& response, const IMethodNode& functionNode, ParamType &params);
    static QSharedPointer<IResponseWare> createStringReturnInstance(void** params);
    static QSharedPointer<IResponseWare> createInterfaceReturnInstance(void** params);

private:
    static void initSystemTypes();
    static void initMultiPartTypes();
    static void initCookiePartTypes();
    static void initBeanTypes();
    static void initJudgeTypes();

private:
    virtual void task() final;  // TODO: 这个没有注册，是怎么回事？
};

$PackageWebCoreEnd
