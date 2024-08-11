#pragma once

#include <iostream>
#include <string>
#include <typeinfo>
#include "core/util/IPackageUtil.h"

$PackageWebCoreBegin

template<typename T, bool enabled=true>
struct ITraceUnit
{
    ITraceUnit() {
        if constexpr (enabled){
            std::cout << "Default constructor called for " << getClassName() << std::endl;
        }
    }

    ITraceUnit(const ITraceUnit &other) {
        if constexpr (enabled){
            std::cout << "Copy constructor called for " << getClassName() << std::endl;
        }
    }

    ITraceUnit& operator=(const ITraceUnit &other) {
        if constexpr (enabled){
            std::cout << "Copy assignment operator called for " << getClassName() << std::endl;
        }
        return *this;
    }

    ITraceUnit(ITraceUnit &&other) noexcept {
        if constexpr (enabled){
            std::cout << "Move constructor called for " << getClassName() << std::endl;
        }
    }

    ITraceUnit& operator=(ITraceUnit &&other) noexcept {
        if constexpr (enabled){
            std::cout << "Move assignment operator called for " << getClassName() << std::endl;
        }
        return *this;
    }

    ~ITraceUnit() {
        if constexpr (enabled){
            std::cout << "Destructor called for " << getClassName() << std::endl;
        }
    }

private:
    std::string getClassName() const {
        return typeid(T).name();
    }
};

$PackageWebCoreEnd
