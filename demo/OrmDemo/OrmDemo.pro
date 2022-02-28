QT -= gui

QT += xml network sql

CONFIG += c++11 console
CONFIG -= app_bundle

DEFINES += QT_DEPRECATED_WARNINGS

include(../../src/src.pri)

SOURCES += \
        SqliteDatabase.cpp \
        UserBean.cpp \
        UserModel.cpp \
        UserTable.cpp \
        main.cpp

HEADERS += \
    SqliteDatabase.h \
    UserBean.h \
    UserModel.h \
    UserTable.h
