#pragma once

#include "core/bean/ITypeMarshalInstantInterface.h"
#include "core/bean/ITypeMarshalTaskInterface.h"

class IBeanDateSerialize : public ITypeMarshalTaskInterface<IBeanDateSerialize, QDate>
{
public:
    IBeanDateSerialize() = default;

    virtual IJson serialize(const void *ptr) const final;
    virtual bool deserialize(void* ptr, const IJson& value) const final;
};
