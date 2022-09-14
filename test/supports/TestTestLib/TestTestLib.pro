QT -= gui

QT += testlib

CONFIG += c++11 console
CONFIG -= app_bundle

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        TestCase.cpp \
        main.cpp

include(../../../src/IWebCore.pri)

HEADERS += \
    TestCase.h
