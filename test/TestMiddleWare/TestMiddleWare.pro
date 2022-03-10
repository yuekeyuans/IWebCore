QT -= gui

QT += core xml network sql

CONFIG += c++11 console
CONFIG -= app_bundle

include(../../src/IWebCore.pri)

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        main.cpp \
        middleWare/PostInterceptorTest.cpp

HEADERS += \
    middleWare/PostInterceptorTest.h

