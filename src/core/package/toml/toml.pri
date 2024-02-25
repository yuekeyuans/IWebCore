INCLUDEPATH += $$PWD

QT += network sql xml testlib

PRECOMPILED_HEADER = $$PWD/core/base/IHeaderUtil.h

HEADERS += \
#    $$PWD/ITomlUtil.h \
    $$PWD/toml.hpp \
    $$PWD/toml/color.hpp \
    $$PWD/toml/combinator.hpp \
    $$PWD/toml/comments.hpp \
    $$PWD/toml/datetime.hpp \
    $$PWD/toml/exception.hpp \
    $$PWD/toml/from.hpp \
    $$PWD/toml/get.hpp \
    $$PWD/toml/into.hpp \
    $$PWD/toml/lexer.hpp \
    $$PWD/toml/literal.hpp \
    $$PWD/toml/macros.hpp \
    $$PWD/toml/parser.hpp \
    $$PWD/toml/region.hpp \
    $$PWD/toml/result.hpp \
    $$PWD/toml/serializer.hpp \
    $$PWD/toml/source_location.hpp \
    $$PWD/toml/storage.hpp \
    $$PWD/toml/string.hpp \
    $$PWD/toml/traits.hpp \
    $$PWD/toml/types.hpp \
    $$PWD/toml/utility.hpp \
    $$PWD/toml/value.hpp \
    $$PWD/toml/version.hpp

#SOURCES += \
#    $$PWD/ITomlUtil.cpp





