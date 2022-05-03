QT -= gui

QT += core network testlib xml

CONFIG += c++11 console
CONFIG -= app_bundle

DEFINES += QT_DEPRECATED_WARNINGS

include(../../../src/IWebCore.pri)
SOURCES += \
        DataBean.cpp \
        TestBeanListMapConvertion.cpp \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    DataBean.h \
    TestBeanListMapConvertion.h
