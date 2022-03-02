#pragma once
#include "base/IPreProcessorUtil.h"
#include "bean/IBeanPreProcessor.h"
#include "configuration/IConfigurationPreProcessor.h"

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

