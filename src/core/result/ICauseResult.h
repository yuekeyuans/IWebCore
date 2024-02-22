#pragma once

#include <type_traits>

#include "IResult.h"

template<typename T>
struct ICauseResult
{
    ICauseResult(T&& value_, std::string cause, bool ok_ = false) : m_value(value_), m_ok(ok_), m_cause(std::move(cause))
    {
    }

    ICauseResult(T&& value_, bool ok_ = true, std::string cause = {}) : m_value(value_), m_ok(ok_), m_cause(std::move(cause))
    {
    }

    template<typename U=T>
    ICauseResult(IResult<U> result) : m_value(std::move(result.m_value)), m_ok(result.m_ok)
    {
    }

    operator T&() {
        return m_value;
    }

    operator IResult<T>(){
        return {static_cast<T>(m_value), m_ok};
    }

    T& value(){
        return m_value;
    }

    bool isOk() {
        return m_ok;
    }

    std::string getCause() {
        return m_cause;
    }

private:
    T m_value;
    bool m_ok;
    std::string m_cause;
};
