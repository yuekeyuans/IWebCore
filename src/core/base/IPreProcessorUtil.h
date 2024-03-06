#pragma once

#define PP_EXPAND(X) X    // for MSVC10 compatibility
#define PP_JOIN(X, Y) X##Y
#define PP_STRING(X) #X
#define PP_NARG(...) PP_EXPAND( PP_NARG_(__VA_ARGS__, PP_RSEQ_N()) )
#define PP_NARG_(...) PP_EXPAND( PP_ARG_N(__VA_ARGS__) )
#define PP_ARG_N(_1, _2, _3, _4, _5, _6, _7, _8, _9, N, ...) N
#define PP_RSEQ_N() 9, 8, 7, 6, 5, 4, 3, 2, 1, 0

#define $UseBareInstance(klassName) \
    public: \
        static klassName* instance(){ \
            static klassName m_instance; \
            return &m_instance; \
        } \
    private:

// TODO: 这个类型需要检查，看看是否需要全部删除
#define $UseInstance(klassName) \
    Q_DISABLE_COPY_MOVE(klassName)\
    $UseBareInstance(klassName)


#define $UseDataPtr(klass)   \
private:    \
    Q_DECLARE_PRIVATE(klass);    \
    std::shared_ptr<klass##Private> d_ptr {nullptr};
