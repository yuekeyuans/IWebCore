#pragma once

#include "core/config/IConfigPreProcessor.h"

#define $EnableControllerPrint(boolValue) \
    PP_PRIVILIGE_CONTEXT_CONFIG(EnableControllerPrint, SYSTEM_CONTROLLER_PRINT, boolValue)

#define $SetIpAddress(value)    \
    PP_PROFILE_CONFIG(SetIpAddress, http.ip, value)

#define $SetIpPort(value)   \
    PP_PROFILE_CONFIG(SetIpPort, http.port, value)


#define $SetFileServiceMapping_(N) $SetFileServiceMapping_##N
#define $SetFileServiceMapping_EVAL(N) $SetFileServiceMapping_(N)
#define $SetFileServiceMapping(...) PP_EXPAND( $SetFileServiceMapping_EVAL(PP_EXPAND( PP_NARG(__VA_ARGS__) ))(__VA_ARGS__) )

#define $SetFileServiceMapping_1(path_) \
    PP_PROFILE_CONFIG(SetFileServiceMapping_location, http.fileService.path, path_) \
    PP_PROFILE_CONFIG(SetFileServiceMapping_url, config.fileService.mapping, "/")

#define $SetFileServiceMapping_2(path_, mapping_) \
    PP_PROFILE_CONFIG(SetFileServiceMapping_location, http.fileService.path, path_) \
    PP_PROFILE_CONFIG(SetFileServiceMapping_url, http.fileService.url, mapping_)
