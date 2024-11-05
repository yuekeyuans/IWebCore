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


#define $UseTaskUnit2(klassName) \
    template<typename T, typename C, bool enabled>  \
    typename klassName <T, C, enabled>:: \
             klassName ## InitPrivate \
             klassName <T, C, enabled>::m_private;    \
    template<typename T, typename C, bool enabled>  \
             klassName<T, C, enabled>:: \
             klassName ## InitPrivate ::     \
             klassName ## InitPrivate ()
