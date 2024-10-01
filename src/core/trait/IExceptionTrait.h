#pragma once
#include "core/util/IPreProcessorUtil.h"

struct IExceptionTrait
{
    static constexpr bool TRAIT_EXCEPTION_DEFINED = true;
};

PP_CLASS_HAS_MEMBER(TRAIT_EXCEPTION_DEFINED)
