#pragma once

#include "core/trait/IExceptionTrait.h"

template<typename T, typename ...U>
struct IBeanTraitInterface : public U...
{
    enum class ErrorHandleType {
        StdOptional,            // 使用 std::optional
        Exception               // 使用 throw exception
    };

    static constexpr inline ErrorHandleType ERROR_HANDLE_TYPE = ErrorHandleType::StdOptional;
};

struct IBeanDefaultTrait : public IBeanTraitInterface<IBeanDefaultTrait>
{
};
