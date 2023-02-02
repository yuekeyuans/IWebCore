#pragma once
#include "core/base/IPreProcessorUtil.h"
#include "core/bean/IBeanPreProcessor.h"
#include "core/configuration/IConfigurationPreProcessor.h"

#define $Column(type, name) \
    static constexpr char const *field_##name = #name ; \
    $BeanField(type, name);

#define $ColumnDeclare(type, name) \
    static constexpr char const *field_##name = #name ; \
    $BeanFieldDeclare(type, name)

#define $AsDatabase(klassName)  \
    $UseInstance(klassName);

#define $AsDialect(klassName) \
    $UseInstance(klassName); \

