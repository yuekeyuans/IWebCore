
#pragma once

#include "core/util/IPreProcessorUtil.h"

#define $AsResponse(klassName)  \
public: \
    klassName(const klassName &rhs) : IResponseInterface(rhs){}   \
    klassName(klassName&& rhs) : IResponseInterface(std::forward<klassName>(rhs)){}     \
    klassName& operator=(klassName &rhs){ IResponseInterface::operator =(rhs);   return *this; }   \
    klassName& operator=(klassName &&rhs){  IResponseInterface::operator =(std::forward<klassName>(rhs));  return *this; }  \
private:    \
    virtual IResponseWare* klassName ::prefixCreate(const QString &data) final {   \
        if constexpr (& klassName :: prefixMatcher != &IResponseWare::prefixMatcher){   \
            return new klassName(data.mid(prefixMatcher().length()));   \
        }   \
        return nullptr; \
    }
