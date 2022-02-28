QT -= gui

QT += sql core network testlib xml

CONFIG += c++11 console
CONFIG -= app_bundle


include(../../../src/src.pri)

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        ConfigBean.cpp \
        ConfigInfo.cpp \
        TestConfig.cpp \
        main.cpp

HEADERS += \
    ConfigBean.h \
    TestConfig.h
