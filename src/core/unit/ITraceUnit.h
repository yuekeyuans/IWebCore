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
            std::cout << getClassName() << " Default constructor called" << std::endl;
        }
    }

    ITraceUnit(const ITraceUnit &) {
        if constexpr (enabled){
            std::cout << getClassName() << " Copy constructor called" << std::endl;
        }
    }

    ITraceUnit& operator=(const ITraceUnit &) {
        if constexpr (enabled){
            std::cout << getClassName() << " Copy assignment operator called" << std::endl;
        }
        return *this;
    }

    ITraceUnit(ITraceUnit &&) noexcept {
        if constexpr (enabled){
            std::cout << getClassName() << " Move constructor called" << std::endl;
        }
    }

    ITraceUnit& operator=(ITraceUnit &&) noexcept {
        if constexpr (enabled){
            std::cout << getClassName() << " Move assignment operator called" << std::endl;
        }
        return *this;
    }

    ~ITraceUnit() {
        if constexpr (enabled){
            std::cout << getClassName() << " Destructor called"<< std::endl;
        }
    }

private:
    std::string getClassName() const {
        return typeid(T).name();
    }
};

$PackageWebCoreEnd
