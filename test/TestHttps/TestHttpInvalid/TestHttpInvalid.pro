QT -= gui
QT += core network xml

CONFIG += c++17 console
CONFIG -= app_bundle

include(../../../src/IWebCore.pri)

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        StatusController.cpp \
        main.cpp \
        test/StatusControllerTest.cpp \
        test/StatusUnitTest.cpp

HEADERS += \
    StatusController.h \
    test/StatusControllerTest.h \
    test/StatusUnitTest.h

