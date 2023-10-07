QT += testlib network sql xml core
QT -= gui

CONFIG += c++17  qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

include(../../../src/IWebCore.pri)

SOURCES +=  \
    OneBean.cpp \
    OneTable.cpp \
    TestGadget.cpp \
    TestMain.cpp \
    TestTable.cpp

HEADERS += \
    OneBean.h \
    OneTable.h \
    TestGadget.h \
    TestTable.h
