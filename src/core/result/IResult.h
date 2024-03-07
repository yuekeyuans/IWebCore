#pragma once

#include <type_traits>

template<typename T>
struct IResult
{
    IResult(T value, bool ok = true);
    operator T&();
    T& value();
    bool isOk();

public:
    T m_value;
    bool m_ok;

private:
    friend struct IConstResult<T>;
    friend struct ICauseResult<T>;
};

template<typename T>
inline IResult<T>::IResult(T value, bool ok) :m_value(std::forward<T>(value)), m_ok(ok)
{
}

template<typename T>
inline IResult<T>::operator T&() {
    return m_value;
}

template<typename T>
inline T & IResult<T>::value() {
    return m_value;
}

template<typename T>
inline bool IResult<T>::isOk() {    // 这个强制手动判断
    return m_ok;
}