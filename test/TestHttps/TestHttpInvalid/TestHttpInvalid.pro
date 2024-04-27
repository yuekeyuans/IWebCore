QT -= gui
QT += core network xml

CONFIG += c++17 console
CONFIG -= app_bundle

include(../../../src/IWebCore.pri)

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        StatusController.cpp \
        main.cpp \
        InvalidController.cpp \
        test/InvalidControllerTest.cpp \
        test/StatusControllerTest.cpp \
        test/StatusUnitTest.cpp \
        test/TestInvalid.cpp

HEADERS += \
    StatusController.h \
    InvalidController.h \
    test/InvalidControllerTest.h \
    test/StatusControllerTest.h \
    test/StatusUnitTest.h \
    test/TestInvalid.h

