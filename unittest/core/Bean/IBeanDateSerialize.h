#pragma once

#include "core/bean/IBeanSerializableInterface.h"

class IBeanDateSerialize : public IBeanSerializableInterface<IBeanDateSerialize, QDate>
{
public:
    IBeanDateSerialize() = default;

    virtual IJson serialize(const void *ptr) const final;
    virtual bool deserialize(void* ptr, const IJson& value) const final;
};
