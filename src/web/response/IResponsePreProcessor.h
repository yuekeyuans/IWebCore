
#pragma once

#include "core/base/IPreProcessorUtil.h"

#define $AsResponse(klassName)  \
public: \
    klassName(const klassName &rhs) : IResponseInterface(rhs){}   \
    klassName(klassName&& rhs) : IResponseInterface(std::forward<klassName>(rhs)){}     \
    klassName& operator=(klassName &rhs){ IResponseInterface::operator =(rhs);   return *this; }   \
    klassName& operator=(klassName &&rhs){  IResponseInterface::operator =(std::forward<klassName>(rhs));  return *this; }
