#pragma once

#include "core/trait/IExceptionTrait.h"

template<typename T, typename ...U>
struct IBeanTraitInterface : public U...
{
    enum class ErrorHandleType {
        Optional,
        Exception
    };

    static constexpr inline ErrorHandleType ERROR_HANDLE_TYPE = ErrorHandleType::Optional;
};

struct IBeanDefaultTrait : public IBeanTraitInterface<IBeanDefaultTrait>
{
};
