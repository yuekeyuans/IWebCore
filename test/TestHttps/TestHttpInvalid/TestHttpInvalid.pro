QT -= gui
QT += core network xml

CONFIG += c++17 console
CONFIG -= app_bundle

include(../../../src/IWebCore.pri)

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        StatusController.cpp \
        main.cpp

HEADERS += \
    StatusController.h

