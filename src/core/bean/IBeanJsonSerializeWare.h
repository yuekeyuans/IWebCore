#pragma once

$PackageWebCoreBegin

struct IBeanJsonSerializeWare
{
public:
    IBeanJsonSerializeWare() = default;
    virtual ~IBeanJsonSerializeWare() = default;

public:
    bool isMatch(const char* data);
    virtual IJson serialize(const void* ptr) const = 0;
    virtual bool deserialize(void* ptr, const IJson& json) const = 0;

protected:
    virtual const char* getTypeName() const = 0;
};

inline bool IBeanJsonSerializeWare::isMatch(const char *data)
{
    const char* name = getTypeName();
    return (name == data || strcmp(name, data) == 0);
}

$PackageWebCoreEnd
