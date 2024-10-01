#pragma once

#include "core/trait/IExceptionTrait.h"

template<typename T, typename ...U>
struct IBeanTraitInterface : public U...
{
};

struct IBeanDefaultTrait : public IBeanTraitInterface<IBeanDefaultTrait>
{

};
