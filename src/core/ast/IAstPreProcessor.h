#pragma once

#define $AsAst(klassName)   \
    klassName* instance(){  \
        static klassName m_instance; \
        return &m_instance; \
    }
