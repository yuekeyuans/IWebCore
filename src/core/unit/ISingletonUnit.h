#pragma once

template<typename T>
struct ISingletonUnit
{
protected:
    ISingletonUnit() = default;
    ~ISingletonUnit() = default;

    ISingletonUnit(const ISingletonUnit&) = delete;
    ISingletonUnit& operator=(const ISingletonUnit&) = delete;

public:
    static T* instance() {
        static T instance;
        return &instance;
    }
};

