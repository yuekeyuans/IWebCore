QT -= gui

CONFIG += c++17 console
CONFIG -= app_bundle

include(../../../src/IWebCore.pri)

DEFINES += QMAKE_PROJECT_DIR=\\\"$$PWD\\\"

SOURCES += \
        bean/StudentBean.cpp \
#        controller/NotFoundInvalidHandler.cpp \
    controller/ArgumentTypeController.cpp \
        controller/ReturnTypeController.cpp \
        main.cpp

HEADERS += \
    bean/StudentBean.h \
#    controller/NotFoundInvalidHandler.h \
    controller/ArgumentTypeController.h \
    controller/RequestAndResponseParameterController.h \
    controller/ReturnTypeController.h
