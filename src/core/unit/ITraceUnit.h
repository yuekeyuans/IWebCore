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
            std::cout << getClassName() << "Default constructor called for " << std::endl;
        }
    }

    ITraceUnit(const ITraceUnit &other) {
        if constexpr (enabled){
            std::cout << getClassName() << "Copy constructor called for " << std::endl;
        }
    }

    ITraceUnit& operator=(const ITraceUnit &other) {
        if constexpr (enabled){
            std::cout << getClassName() << "Copy assignment operator called for " << std::endl;
        }
        return *this;
    }

    ITraceUnit(ITraceUnit &&other) noexcept {
        if constexpr (enabled){
            std::cout << getClassName() << "Move constructor called for " << std::endl;
        }
    }

    ITraceUnit& operator=(ITraceUnit &&other) noexcept {
        if constexpr (enabled){
            std::cout << getClassName() << "Move assignment operator called for " << std::endl;
        }
        return *this;
    }

    ~ITraceUnit() {
        if constexpr (enabled){
            std::cout << getClassName()  << "Destructor called for "<< std::endl;
        }
    }

private:
    std::string getClassName() const {
        return typeid(T).name();
    }
};

$PackageWebCoreEnd
