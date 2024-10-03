#pragma once

#include "core/bean/IBeanTypeMarshalInstantInterface.h"
#include "core/bean/IBeanTypeMarshalTaskInterface.h"

class IBeanDateSerialize : public IBeanTypeMarshalTaskInterface<IBeanDateSerialize, QDate>
{
public:
    IBeanDateSerialize() = default;

    virtual IJson serialize(const void *ptr) const final;
    virtual bool deserialize(void* ptr, const IJson& value) const final;
};
