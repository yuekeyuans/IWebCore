
#pragma once

#include "core/util/IPreProcessorUtil.h"
#include "core/util/IStringUtil.h"

#define $AsResponse(klassName)  \
public: \
    klassName(const klassName &rhs) : IResponseInterface(rhs){}   \
    klassName(klassName&& rhs) : IResponseInterface(std::move(rhs)){}     \
    klassName& operator=(klassName &rhs){ IResponseInterface::operator =(rhs);   return *this; }   \
    klassName& operator=(klassName &&rhs){  IResponseInterface::operator =(std::move(rhs));  return *this; }  \
private:    \
    virtual IResponseWare* klassName ::prefixCreate(const std::string &data) final {   \
        if constexpr (& klassName :: prefixMatcher != &IResponseWare::prefixMatcher){   \
            return new klassName(IStringUtil::mid(data, prefixMatcher().length()));   \
        }   \
        return nullptr; \
    }


