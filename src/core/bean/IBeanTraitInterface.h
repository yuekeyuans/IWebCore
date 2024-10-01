#pragma once

#include "core/trait/IExceptionTrait.h"

template<typename T, typename ...U>
struct IBeanTraitInterface : public U...
{
    static constexpr inline bool CONFIG_USE_OPTIONAL = true;
};

struct IBeanDefaultTrait : public IBeanTraitInterface<IBeanDefaultTrait>
{

};
