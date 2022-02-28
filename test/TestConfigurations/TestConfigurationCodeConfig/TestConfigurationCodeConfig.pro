QT -= gui

QT += sql core network testlib xml

CONFIG += c++11 console
CONFIG -= app_bundle


include(../../../src/src.pri)

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        ApplicationInitialConfiguration.cpp \
        DataBean.cpp \
        DataInitialWireBean.cpp \
        TestConfig.cpp \
        TestFunctionCallConfiger.cpp \
        main.cpp

HEADERS += \
    ApplicationInitialConfiguration.h \
    DataBean.h \
    DataInitialWireBean.h \
    TestConfig.h \
    TestFunctionCallConfiger.h

DISTFILES += \
    config.json

RESOURCES += \
    res.qrc
