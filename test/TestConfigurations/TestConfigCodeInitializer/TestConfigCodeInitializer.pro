QT -= gui

QT += sql core network testlib xml

CONFIG += c++17 console
CONFIG -= app_bundle


include(../../../src/IWebCore.pri)

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        ConfigBean.cpp \
        ConfigInfo.cpp \
        TestConfig.cpp \
        main.cpp

HEADERS += \
    ConfigBean.h \
    TestConfig.h
