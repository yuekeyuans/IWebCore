QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

include(../../../src/IWebCore.pri)

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        main.cpp


# 目的，在这个子项目当中完成一个完整的 listener, interceptor 设计，并达到一定要求
