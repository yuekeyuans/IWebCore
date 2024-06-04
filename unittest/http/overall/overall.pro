QT -= gui

CONFIG += c++17 console
CONFIG -= app_bundle

include(../../../src/IWebCore.pri)

DEFINES += QT_DEPRECATED_WARNINGS


SOURCES += \
        main.cpp
