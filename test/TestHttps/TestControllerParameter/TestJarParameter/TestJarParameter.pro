QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

DEFINES += QT_DEPRECATED_WARNINGS

include(../../../../src/IWebCore.pri)
SOURCES += \
        controller/CookieJarController.cpp \
        main.cpp

HEADERS += \
    controller/CookieJarController.h
