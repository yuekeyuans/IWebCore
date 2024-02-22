#pragma once

#include <type_traits>

template<typename T>
struct IResult
{
    IResult(T&& value, bool ok = true) :m_value(std::forward<T>(value)), m_ok(ok)
    {
    }

    operator T() {
        return m_value;
    }

    T& value() {
        return m_value;
    }

    bool isOk() {    // 这个强制手动判断
        return m_ok;
    }

public:
    T m_value;
    bool m_ok;
};

