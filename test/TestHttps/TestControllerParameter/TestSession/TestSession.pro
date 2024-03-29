QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle


DEFINES += QT_DEPRECATED_WARNINGS

include(../../../../src/IWebCore.pri)

SOURCES += \
        ISessionController.cpp \
        MemorySession.cpp \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    ISessionController.h \
    MemorySession.h
