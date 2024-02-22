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
    template<typename ...Args>
    static T* instance(Args&& ...args) {
        static T instance{std::forward<Args>(args)...};
        return &instance;
    }
};

