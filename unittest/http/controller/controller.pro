QT -= gui

CONFIG += c++17 console
CONFIG -= app_bundle

include(../../../src/IWebCore.pri)
SOURCES += \
        controller/MethodParameterResolveTestController.cpp \
        main.cpp

HEADERS += \
    controller/MethodParameterResolveTestController.h

