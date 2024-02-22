#pragma once

#define $AsTaskUnit(klassName) \
private:    \
    class klassName ## InitPrivate{ \
    public: \
        klassName ## InitPrivate(); \
    };  \
    static klassName ## InitPrivate m_private;  \
    virtual void* klassName ## InitPrivateTouch(){  \
        return &m_private;  \
    }

#define $UseTaskUnit(klassName) \
    template<typename T, bool enabled>  \
    typename klassName <T, enabled>:: \
             klassName ## InitPrivate \
             klassName <T, enabled>::m_private;    \
    template<typename T, bool enabled>  \
             klassName<T, enabled>:: \
             klassName ## InitPrivate ::     \
             klassName ## InitPrivate ()
