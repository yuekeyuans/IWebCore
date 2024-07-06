QT -= gui

CONFIG += c++17 console
CONFIG -= app_bundle

include(../../../src/IWebCore.pri)
SOURCES += \
        main.cpp

HEADERS += \
    controller/RequestAndResponseParameterController.h

