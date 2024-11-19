QT -= gui

QT += xml network sql

CONFIG += c++11 console
CONFIG -= app_bundle

include(../../src/IWebCore.pri)

INCLUDEPATH += E:/project/libs/boost/boost_1_77_0/

DEFINES += QT_DEPRECATED_WARNINGS


SOURCES += \
        EmailBean.cpp \
        SqliteDatabase.cpp \
        UserBean.cpp \
        UserModel.cpp \
        main.cpp

HEADERS += \
    EmailBean.h \
    SqliteDatabase.h \
    UserBean.h \
    UserModel.h
