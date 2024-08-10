QT -= gui

CONFIG += c++17 console
CONFIG -= app_bundle

DEFINES += QT_DEPRECATED_WARNINGS

include(../../../src/IWebCore.pri)

SOURCES += \
        NameBean.cpp \
        main.cpp

HEADERS += \
    NameBean.h
