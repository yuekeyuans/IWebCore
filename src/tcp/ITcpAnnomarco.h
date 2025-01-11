#pragma once

#include "core/config/IConfigPreProcessor.h"

#define $SetTcpIp(value)    \
    PP_PROFILE_CONFIG(SetTcpIpAddress, /tcp/ip, value)

#define $SetTcpPort(value)   \
    PP_PROFILE_CONFIG(SetTcpIpPort, /tcp/port, value)

#define $SetTcpResolverFactory(value)   \
    PP_PROFILE_CONFIG(SetTcpResolverFactory, /tcp/resolverFactory, value)
