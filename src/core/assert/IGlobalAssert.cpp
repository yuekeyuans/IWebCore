#include "IGlobalAssert.h"

$PackageWebCoreBegin

inline void IGlobalAssert::loadAssert()
{
    // IApplication
    addFatal("IApplication_not_created", "you can not get any IApplication instance when IApplication not created");

    /// global
    addFatal("Assert_Load_Json_Error", "your json format is not correct");
    addFatal("UnImplimentedMethod", "this method is not implimented.");
    addFatal("JsonArrayMergeMismatch", "Merge json array must both are array type");
    addFatal("JsonObjectMergeMismatch", "Merge object array must both are object type");
    addWarn("JsonFetchNotSupportArrary", "fetch json content not support path with array");
    addWarn("JsonMergeWarnWithArray", "add json content to context not support path with array currently");

    /// macro
    addFatal("EnableBluePrintParamError", "");

    /// context
    addFatal("ConfigurationMayNotInitialized"
             , "the configuration will complete at the begin of main. "
               "when you use configuration when configuration not complete, "
               "this warning popup."
             , "change your code, or ignore this warning");

    addFatal("ConfigurationMergeJsonValueError");
    addFatal("ConfigurationCovertYamlFailError");
    addFatal("ConfigurationResolveJsonError");
    addFatal("ContextAddPathInvalid");
    addFatal("ContextRemovePathInvalid", "remove path can not be empty");
    addFatal("ContextObjectError", "Configuration`s top level must be an object other than a array. Please use key-value pair to register configuration");
    addFatal("ContextMergeError");

    /// task
    addFatal("TaskDeferRegisterNotAllowed");
    addFatal("TaskShouldNotBeRegistered", "task can not be registered when the task run finished");
    addWarn("CatagoryRangeExceed", "catagory range ought to be in 0 and 100");
    addWarn("TaskRangeExceed", "catagory range ought to be in 0 and 100");
    addWarn("TaskWithErrorCatagory", "this task`s catagory does not exist, please check your code");

    // unit
    addFatal("SingletonInstanceCreateError", "error with singleton instance, you should not create anyother instance of this");

}

$PackageWebCoreEnd
