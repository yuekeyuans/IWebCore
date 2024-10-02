#pragma once

#include "core/bean/ITypeMarshalInterface.h"

class IBeanDateSerialize : public ITypeMarshalInterface<IBeanDateSerialize, QDate>
{
public:
    IBeanDateSerialize() = default;

    virtual IJson serialize(const void *ptr) const final;
    virtual bool deserialize(void* ptr, const IJson& value) const final;
};
