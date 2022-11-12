QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

DEFINES += QT_DEPRECATED_WARNINGS

include(../../../../src/IWebCore.pri)
SOURCES += \
        controller/CookieJarController.cpp \
        controller/HeaderJarController.cpp \
        controller/IMultiPartJarController.cpp \
        controller/ISessionJarController.cpp \
        main.cpp

HEADERS += \
    controller/CookieJarController.h \
    controller/HeaderJarController.h \
    controller/IMultiPartJarController.h \
    controller/ISessionJarController.h
