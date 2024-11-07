QT -= gui

CONFIG += c++17 console
CONFIG -= app_bundle

include(../../../src/IWebCore.pri)
SOURCES += \
        bean/StudentBean.cpp \
        controller/NotFoundInvalidHandler.cpp \
        controller/ReturnTypeController.cpp \
        main.cpp

HEADERS += \
    bean/StudentBean.h \
    controller/NotFoundInvalidHandler.h \
    controller/RequestAndResponseParameterController.h \
    controller/ReturnTypeController.h

