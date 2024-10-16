QT -= gui

CONFIG += c++17 console
CONFIG -= app_bundle

DEFINES += QT_DEPRECATED_WARNINGS

include(../../../src/IWebCore.pri)

SOURCES += \
        IBeanDateSerialize.cpp \
        NameBean.cpp \
        PersonBean.cpp \
        main.cpp

HEADERS += \
    IBeanDateSerialize.h \
    JsonHeader.h \
    NameBean.h \
    PersonBean.h
