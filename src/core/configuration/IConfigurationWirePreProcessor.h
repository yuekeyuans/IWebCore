#pragma once

#define $AutoWireDeclare_4(type, name, path, group) \
    Q_CLASSINFO(PP_STRING(iwebConfigWire__ ## name ## _name),  PP_STRING(name)); \
    Q_CLASSINFO(PP_STRING(iwebConfigWire__ ## name ## _path),  PP_STRING(path)); \
    Q_CLASSINFO(PP_STRING(iwebConfigWire__ ## name ## _group), PP_STRING(group)); \
    $BeanFieldDeclare(type, name)

#define $AutoWireDeclare_3(type, name, path) \
    Q_CLASSINFO(PP_STRING(iwebConfigWire__ ## name ## _name),  PP_STRING(name)); \
    Q_CLASSINFO(PP_STRING(iwebConfigWire__ ## name ## _path),  PP_STRING(path)); \
    $BeanFieldDeclare(type, name)

#define $AutoWireDeclare_2(type, name) \
    Q_CLASSINFO(PP_STRING(iwebConfigWire__ ## name ## _name),  PP_STRING(name)); \
    Q_CLASSINFO(PP_STRING(iwebConfigWire__ ## name ## _path),  PP_STRING(name)); \
    $BeanFieldDeclare(type, name)

#define $AutoWireDeclare_(N) $AutoWireDeclare_##N
#define $AutoWireDeclare_EVAL(N) $AutoWireDeclare_(N)
#define $AutoWireDeclare(...) PP_EXPAND( $AutoWireDeclare_EVAL(PP_EXPAND( PP_NARG(__VA_ARGS__) ))(__VA_ARGS__) )

#define $AutoWire_4(type, name, group, path) \
    $AutoWireDeclare_4(type, name, group, path) \
    type name{};

#define $AutoWire_3(type, name, path) \
    $AutoWireDeclare_3(type, name, path) \
    type name {};

#define $AutoWire_2(type, name) \
    $AutoWireDeclare_2(type, name) \
    type name {};

#define $AutoWire_(N) $AutoWire_##N
#define $AutoWire_EVAL(N) $AutoWire_(N)
#define $AutoWire(...) PP_EXPAND( $AutoWire_EVAL(PP_EXPAND( PP_NARG(__VA_ARGS__) ))(__VA_ARGS__) )

#define $OptionWireDeclare_4(type, name, path, group) \
    Q_CLASSINFO(PP_STRING(iwebConfigWire__ ## name ## _option),  PP_STRING(name)); \
    Q_CLASSINFO(PP_STRING(iwebConfigWire__ ## name ## _name),  PP_STRING(name)); \
    Q_CLASSINFO(PP_STRING(iwebConfigWire__ ## name ## _path),  PP_STRING(path)); \
    Q_CLASSINFO(PP_STRING(iwebConfigWire__ ## name ## _group), PP_STRING(group)); \
    $BeanFieldDeclare(type, name)

#define $OptionWireDeclare_3(type, name, path) \
    Q_CLASSINFO(PP_STRING(iwebConfigWire__ ## name ## _option),  PP_STRING(name)); \
    Q_CLASSINFO(PP_STRING(iwebConfigWire__ ## name ## _name),  PP_STRING(name)); \
    Q_CLASSINFO(PP_STRING(iwebConfigWire__ ## name ## _path),  PP_STRING(path)); \
    $BeanFieldDeclare(type, name)

#define $OptionWireDeclare_2(type, name) \
    Q_CLASSINFO(PP_STRING(iwebConfigWire__ ## name ## _option),  PP_STRING(name)); \
    Q_CLASSINFO(PP_STRING(iwebConfigWire__ ## name ## _name),  PP_STRING(name)); \
    Q_CLASSINFO(PP_STRING(iwebConfigWire__ ## name ## _path),  PP_STRING(name)); \
    $BeanFieldDeclare(type, name)

#define $OptionWireDeclare_(N) $OptionWireDeclare_##N
#define $OptionWireDeclare_EVAL(N) $OptionWireDeclare_(N)
#define $OptionWireDeclare(...) PP_EXPAND( $OptionWireDeclare_EVAL(PP_EXPAND( PP_NARG(__VA_ARGS__) ))(__VA_ARGS__) )

#define $OptionWire_4(type, name, group, path) \
    $OptionWireDeclare_4(type, name, group, path) \
    type name{};

#define $OptionWire_3(type, name, path) \
    $OptionWireDeclare_3(type, name, path) \
    type name {};

#define $OptionWire_2(type, name) \
    $OptionWireDeclare_2(type, name) \
    type name {};

#define $OptionWire_(N) $OptionWire_##N
#define $OptionWire_EVAL(N) $OptionWire_(N)
#define $OptionWire(...) PP_EXPAND( $OptionWire_EVAL(PP_EXPAND( PP_NARG(__VA_ARGS__) ))(__VA_ARGS__) )

