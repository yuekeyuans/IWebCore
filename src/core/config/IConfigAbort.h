#pragma once

#include "core/abort/IAbortInterface.h"

$PackageWebCoreBegin

class IConfigAbort : public IAbortInterface<IConfigAbort>
{
    $AsAbort(
        ContextAddPathInvalid,
        ContextMergeError,
        JsonArrayMergeMismatch,
        JsonMergeFatalWithArray,
        JsonFetchNotSupportArrary,
        ConfigurationCovertYamlFailError,
        ConfigurationResolveJsonError
    )
protected:
    virtual QMap<int, QString> abortDescription() const final{
        return {
            {ContextAddPathInvalid, "ContextAddPathInvalid"},
            {ContextMergeError, "ContextMergeError"},
            {JsonArrayMergeMismatch, "Merge json array must both are array type"},
            {JsonMergeFatalWithArray, "add json content to context not support path with array in middle"},
            {JsonFetchNotSupportArrary, "fetch json content not support path with array"},
            {ConfigurationCovertYamlFailError, ""},
            {ConfigurationResolveJsonError, ""}
        };
    }
};

$PackageWebCoreEnd
