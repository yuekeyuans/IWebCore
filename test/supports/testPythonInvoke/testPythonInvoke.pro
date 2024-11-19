# this project is using python scripts to run test

QT -= gui

QT += testlib

CONFIG += c++11 console
CONFIG -= app_bundle

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        main.cpp

include(../../../src/IWebCore.pri)
