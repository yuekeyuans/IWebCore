QT -= gui

QT += sql network xml

CONFIG += c++11 console
CONFIG -= app_bundle

DEFINES += QT_DEPRECATED_WARNINGS

include(../../src/IWebCore.pri)

SOURCES += \
        MyController.cpp \
        main.cpp

HEADERS += \
    MyController.h
