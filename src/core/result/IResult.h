#pragma once

#include <type_traits>

#pragma once

#include <type_traits>
#include <string>

template<typename T>
struct IConstResult;

template<typename T>
struct ICauseResult;

template<typename T>
struct IResult
{
    IResult(T&& value, bool ok = true);
    operator T&();
    T& value();
    bool isOk();

private:
    T m_value;
    bool m_ok;

private:
    friend struct IConstResult<T>;
    friend struct ICauseResult<T>;
};

template<typename T>
struct IConstResult
{
    IConstResult(T&& value, bool ok = true);
    IConstResult(const IResult<T>& value);
    IConstResult(IResult<T>&& value);                // TODO: 这个不对，没有办法完全处理右值引用，需要仔细思考一下
    IConstResult& operator =(T) = delete;
    IConstResult& operator =(const IConstResult&) = delete;
    IConstResult& operator = (IConstResult&& value);
    operator const T&();
    const T& value();
    bool isOk();

private:
    T m_value;
    bool m_ok;
};

template<typename T>
struct ICauseResult
{
    ICauseResult(T&& value_, std::string cause, bool ok_ = false);
    ICauseResult(T&& value_, bool ok_ = true, std::string cause = {});
    ICauseResult(IResult<T> result);
    ICauseResult(IConstResult<T>result);

    operator T&();

    operator IResult<T>();

    operator IConstResult<T>();

    bool isOk();

    std::string getCause();

public:
    T m_value;
    bool m_ok;
    std::string m_cause;
};

template<typename T>
inline IResult<T>::IResult(T && value, bool ok) :m_value(std::forward<T>(value)), m_ok(ok)
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

template<typename T>
inline IConstResult<T>::IConstResult(T && value, bool ok) :m_value(std::forward<T>(value)), m_ok(ok)
{
}

template<typename T>
inline IConstResult<T>::IConstResult(const IResult<T>& value) : m_value(value.value), m_ok(value.m_ok) {
    std::cout << "hello world";
    m_value = value.m_value;
    m_ok = value.m_ok;
}

// TODO: 这个不对，没有办法完全处理右值引用，需要仔细思考一下
template<typename T>
inline IConstResult<T>::IConstResult(IResult<T>&& value) : m_value(std::move(value.m_value)), m_ok(value.m_ok)
{
}

template<typename T>
IConstResult<T>& IConstResult<T>::operator = (IConstResult<T>&& value) {
    std::swap(m_value, value.m_value);
    m_ok = value.m_ok;
    return *this;
}

template<typename T>
IConstResult<T>::operator const T &() {
    return m_value;
}

template<typename T>
inline const T & IConstResult<T>::value() {
    return m_value;
}

template<typename T>
inline bool IConstResult<T>::isOk() {    // 这个强制手动判断
    return m_ok;
}

template<typename T>
inline ICauseResult<T>::ICauseResult(T && value_, std::string cause, bool ok_) : m_value(value_), m_ok(ok_), m_cause(std::move(cause))
{
}

template<typename T>
inline ICauseResult<T>::ICauseResult(T && value_, bool ok_, std::string cause) : m_value(value_), m_ok(ok_), m_cause(std::move(cause))
{
}

template<typename T>
inline ICauseResult<T>::ICauseResult(IResult<T> result) : m_value(std::move(result.m_value)), m_ok(result.m_ok)
{
}

template<typename T>
inline ICauseResult<T>::ICauseResult(IConstResult<T> result) : m_value(result.m_value), m_ok(result.m_ok)
{
}

template<typename T>
inline ICauseResult<T>::operator T&() {
    return m_value;
}

template<typename T>
inline bool ICauseResult<T>::isOk() {
    return m_ok;
}

template<typename T>
inline std::string ICauseResult<T>::getCause() {
    return m_cause;
}

template<typename T>
inline ICauseResult<T>::operator IConstResult<T>() {
    return { static_cast<T>(m_value), m_ok };
}

template<typename T>
inline ICauseResult<T>::operator IResult<T>() {
    return { static_cast<T>(m_value), m_ok };
}
