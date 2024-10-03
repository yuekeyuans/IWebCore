#pragma once

#include "core/util/IHeaderUtil.h"

$PackageWebCoreBegin

struct IBeanTypeMarshalWare
{
public:
    IBeanTypeMarshalWare() = default;
    virtual ~IBeanTypeMarshalWare() = default;

public:
    bool isMatch(const char* data) const;
    virtual IJson serialize(const void* ptr) const = 0;
    virtual bool deserialize(void* ptr, const IJson& json) const = 0;

protected:
    virtual const char* getTypeName() const = 0;
};

inline bool IBeanTypeMarshalWare::isMatch(const char *data) const
{
    const char* name = getTypeName();
    return (name == data || strcmp(name, data) == 0);
}

$PackageWebCoreEnd
