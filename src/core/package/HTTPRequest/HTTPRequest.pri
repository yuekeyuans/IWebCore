INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/HTTPRequest.hpp

win32:LIBS += -lws2_32
