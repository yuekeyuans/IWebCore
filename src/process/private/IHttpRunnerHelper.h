#pragma once

#include "base/IHeaderUtil.h"
#include "common/response/IResponseWare.h"
#include "common/task/IInitializationTaskUnit.h"

$PackageWebCoreBegin

class IRequest;
class IResponse;
struct IFunctionNode;
struct IFunctionParamNode;

class IHttpRunnerHelper : public IInitializationTaskUnit<IHttpRunnerHelper>
{
    $UseInstance(IHttpRunnerHelper)
public:
    using ParamType = void*[11];
    using CreateParamFunType = void*(*)(const IFunctionParamNode& node, IRequest& request);
    using ReleaseParamFunType = bool (*)(const IFunctionParamNode& node, void *obj);

private:
    IHttpRunnerHelper() = default;

public:
    static void createParams(const IFunctionNode& functionNode, ParamType& params, IRequest& request);
    static void *createReturnParam(int paramTypeId);
    static void *createArgParam(const IFunctionParamNode&node, IRequest& request);

    static void destroyParams(const IFunctionNode& functionNode, void **params);
    static void destroyReturnParam(void *obj, int paramTypeId);
    static void destroyArgParam(const IFunctionParamNode& node, void *obj);
    static void resolveReturnValue(IResponse& response, const IFunctionNode& functionNode, ParamType &params);

    static void wrapVoidReturnInstance(IResponse& response, const IFunctionNode& functionNode, ParamType &params);
    static QSharedPointer<IResponseWare> createStringReturnInstance(void** params);
    static QSharedPointer<IResponseWare> createIntReturnInstance(void** params);
    static QSharedPointer<IResponseWare> createJsonValueReturnInstance(void** params);
    static QSharedPointer<IResponseWare> createJsonObjectReturnInstance(void** params);
    static QSharedPointer<IResponseWare> createJsonArrayReturnInstance(void** params);
    static QSharedPointer<IResponseWare> createByteArrayReturnInstance(void** params);
    static QSharedPointer<IResponseWare> createStringListReturnType(void** params);
    static QSharedPointer<IResponseWare> createInterfaceReturnInstance(void** params);

    static void* getParamOfSystem(const IFunctionParamNode& node, IRequest& request);
    static void* getParamOfMultipart(const IFunctionParamNode& node, IRequest& request);
    static void* getParamOfCookie(const IFunctionParamNode& node, IRequest& request);
    static void* getParamOfSession(const IFunctionParamNode& node, IRequest& request);
    static void* getParamOfBean(const IFunctionParamNode& node, IRequest& request);
    static void* getParamOfJsonType(const IFunctionParamNode& node, IRequest& request);
    static void* getParamOfPrimitiveType(const IFunctionParamNode& node, IRequest& request);
    static void* getParamOfStringType(const IFunctionParamNode& node, IRequest& request);

    static bool releaseParamOfSystem(const IFunctionParamNode& node, void *obj);
    static bool releaseParamOfMultipart(const IFunctionParamNode& node, void *obj);
    static bool releaseParamOfCookie(const IFunctionParamNode& node, void *obj);
    static bool releaseParamOfSession(const IFunctionParamNode& node, void *obj);
    static bool releaseParamOfBean(const IFunctionParamNode& node, void *obj);
    static bool releaseParamOfJsonType(const IFunctionParamNode& node, void *obj);
    static bool releaseParamOfPrimitiveType(const IFunctionParamNode& node, void *obj);
    static bool releaseParamOfStringType(const IFunctionParamNode& node, void *obj);

public:
    virtual void task() final;
};

$PackageWebCoreEnd
