#pragma once

#define PP_EXPAND(X) X    // for MSVC10 compatibility
#define PP_JOIN(X, Y) X##Y
#define PP_STRING(X) #X
#define PP_NARG(...) PP_EXPAND( PP_NARG_(__VA_ARGS__, PP_RSEQ_N()) )
#define PP_NARG_(...) PP_EXPAND( PP_ARG_N(__VA_ARGS__) )
#define PP_ARG_N(_1, _2, _3, _4, _5, _6, _7, _8, _9, N, ...) N
#define PP_RSEQ_N() 9, 8, 7, 6, 5, 4, 3, 2, 1, 0

#define $UseDataPtr(klass)   \
private:    \
    std::shared_ptr<klass##Impl> d_ptr {nullptr};
