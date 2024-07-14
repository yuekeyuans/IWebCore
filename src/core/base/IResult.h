#pragma once

#include <type_traits>
#include <optional>

template<typename T>
using IResult = std::optional<T>;

//template<typename T>
//struct IResult
//{
//    IResult(T value, bool ok) : m_value(std::move(value)), m_ok(ok){ }
//    operator const T&(){ return m_value; }
//    explicit operator bool() {return m_ok;}
//    const T& value() const{ return m_value; }
//    bool isOk() const{ return m_ok; }

//public:
//    T m_value;
//    bool m_ok;
//};

//template<>
//struct IResult<bool>
//{
//    IResult(bool value, bool ok) : m_value(std::move(value)), m_ok(ok) { }
////    operator T&();
//    const bool& value() const { return m_value;}
//    bool isOk() const {return m_ok; }
//public:
//    bool m_value;
//    bool m_ok;
//};
