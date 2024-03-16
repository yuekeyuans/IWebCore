
#pragma once

#include "core/base/IPreProcessorUtil.h"
#include "core/base/IMetaUtil.h"
#include "web/response/IResponseWareRaw.h"

#define $AsResponse(klassName)  \
public: \
    klassName(const klassName &rhs) : IResponseInterface(rhs){}   \
    klassName(klassName&& rhs) : IResponseInterface(std::forward<klassName>(rhs)){}  \
    klassName& operator=(klassName &rhs){ this->operator =(rhs);   return *this;  }   \
    klassName& operator=(klassName &&rhs){  this->operator =(std::forward<klassName>(rhs));  return *this; }
