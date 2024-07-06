QT -= gui

CONFIG += c++17 console
CONFIG -= app_bundle

include(../../../src/IWebCore.pri)

SOURCES += \
        IGlobalTest.cpp \
        main.cpp

HEADERS += \
    IGlobalTest.h
