QT -= gui

CONFIG += c++17 console
CONFIG -= app_bundle

include(../../../src/IWebCore.pri)

DEFINES += QT_DEPRECATED_WARNINGS


SOURCES += \
        FormDataController.cpp \
        RequestParameterController.cpp \
        main.cpp \
        test/TestFormDataController.cpp

HEADERS += \
    FormDataController.h \
    RequestParameterController.h \
    test/TestFormDataController.h
