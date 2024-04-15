#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/unit/ISingletonUnit.h"
#include "core/task/default/IInitializationTaskInterface.h"
#include "web/response/IResponseWare.h"

$PackageWebCoreBegin

class IRequest;
class IResponse;
struct IMethodNode;
struct IFunctionNode;
struct IParamNode;

class IControllerParameter  : public IInitializationTaskInterface<IControllerParameter>
{
public:
    using ParamType = void*[11];
    using CreateParamFunType = void*(IControllerParameter::*)(const IParamNode& node, IRequest& request, bool& ok);
    using ReleaseParamFunType = bool (IControllerParameter::*)(const IParamNode& node, void *obj);

public:
    IControllerParameter() = default;

public:
    bool createArguments(const IMethodNode& methodNode, ParamType& params, IRequest& request);
    void destroyArguments(const IMethodNode& node, void **params);
    void resolveReturnValue(IResponse& response, const IMethodNode& functionNode, ParamType &params);

private:
    void *createReturnParam(int paramTypeId);
    void *createArgParam(const IParamNode&node, IRequest& request, bool& ok);
    void destroyReturnParam(void *obj, int paramTypeId);
    void destroyArgParam(const IParamNode& node, void *obj);

private:
    void* getParamOfSystem(const IParamNode& node, IRequest& request, bool& ok);
    void* getParamOfMultipart(const IParamNode& node, IRequest& request, bool& ok);
    void* getParamOfCookiePart(const IParamNode& node, IRequest& request, bool& ok);
    void* getParamOfSession(const IParamNode& node, IRequest& request, bool& ok);
    void* getParamOfBean(const IParamNode& node, IRequest& request, bool& ok);
    void* getParamOfJsonType(const IParamNode& node, IRequest& request, bool& ok);
    void* getParamOfPrimitiveType(const IParamNode& node, IRequest& request, bool& ok);
    void* getParamOfStringType(const IParamNode& node, IRequest& request, bool& ok);

    bool releaseParamOfSystem(const IParamNode& node, void *obj);
    bool releaseParamOfMultipart(const IParamNode& node, void *obj);
    bool releaseParamOfCookiePart(const IParamNode& node, void *obj);
    bool releaseParamOfBean(const IParamNode& node, void *obj);
    bool releaseParamOfJsonType(const IParamNode& node, void *obj);
    bool releaseParamOfPrimitiveType(const IParamNode& node, void *obj);
    bool releaseParamOfStringType(const IParamNode& node, void *obj);

private:
    void wrapVoidReturnInstance(IResponse& response, const IMethodNode& functionNode, ParamType &params);
    QSharedPointer<IResponseWare> createStringReturnInstance(void** params);
    QSharedPointer<IResponseWare> createInterfaceReturnInstance(void** params);

private:
    void initSystemTypes();
    void initMultiPartTypes();
    void initCookiePartTypes();
    void initBeanTypes();
    void initJudgeTypes();

private:
    virtual void task() final;  // TODO: 这个没有注册，是怎么回事？

//private:
//    QVector<int> SystemTypes;
//    QVector<int> MultiPartTypes;
//    QVector<int> CookiePartTypes;
//    QVector<int> BeanTypes;
//    QVector<QVector<int>> JudgeTypes;
};

$PackageWebCoreEnd
