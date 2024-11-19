#pragma once
#include "core/util/IPreProcessorUtil.h"
#include "core/bean/IBeanPreProcessor.h"

#define $Column(type, name) \
    static constexpr char const *field_##name = #name ; \
    $BeanField(type, name);

#define $ColumnDeclare(type, name) \
    static constexpr char const *field_##name = #name ; \
    $BeanFieldDeclare(type, name)

