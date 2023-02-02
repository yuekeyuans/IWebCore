
#pragma once

#include "core/base/IPreProcessorUtil.h"
#include "core/base/IMetaUtil.h"
#include "web/response/IResponseWareRaw.h"

#define PP_AS_RESPONSE(klassName) \
public: \
    klassName(const klassName &rhs){    \
        auto raw = new IResponseWareRaw(*rhs.raw);  \
        delete this->raw;   \
        this->raw = raw;   \
    }   \
    klassName& operator=(klassName &rhs){  \
        auto raw = new IResponseWareRaw(*rhs.raw);  \
        delete this->raw;   \
        this->raw = raw;    \
        return *this;   \
    }   \
    klassName& operator=(klassName &&rhs){  \
        std::swap(this->raw, rhs.raw);  \
        return *this;   \
    }   \
    klassName(klassName&& rhs){ \
        std::swap(this->raw, rhs.raw);  \
    }

#define $AsResponse(klassName)  \
public: \
    $UseInstance(klassName) \
    $UseMetaRegistration(klassName)     \
    PP_AS_RESPONSE(klassName)
