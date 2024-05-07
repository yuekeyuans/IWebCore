QT -= gui

CONFIG += c++17 console
CONFIG -= app_bundle

include(../../../src/IWebCore.pri)

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        lib/ITcpLoopThread.cpp \
        lib/ITcpReceiverInterface.cpp \
        lib/ITcpServerInterface.cpp \
        lib/QHttpServer.cpp \
        lib/TcpRequest.cpp \
        main.cpp

HEADERS += \
    lib/ITcpLoopThread.h \
    lib/ITcpReceiverInterface.h \
    lib/ITcpServerInterface.h \
    lib/QHttpServer.h \
    lib/TcpRequest.h
