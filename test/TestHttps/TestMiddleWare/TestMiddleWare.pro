QT -= gui

QT += core xml network sql

CONFIG += c++11 console
CONFIG -= app_bundle

include(../../../src/IWebCore.pri)

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        controller/TestController.cpp \
        main.cpp \
        middleWare/PostInterceptorTest.cpp

HEADERS += \
    controller/TestController.h \
    middleWare/PostInterceptorTest.h

