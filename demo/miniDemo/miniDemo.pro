QT -= gui

QT += xml network sql

CONFIG += c++11 console
CONFIG -= app_bundle

DEFINES += QT_DEPRECATED_WARNINGS

include(../../src/src.pri)

SOURCES += \
        main.cpp

HEADERS += \
    MyFirstController.h
