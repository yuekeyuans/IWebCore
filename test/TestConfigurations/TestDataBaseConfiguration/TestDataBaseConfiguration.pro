QT -= gui

QT += sql core network testlib xml

CONFIG += c++11 console
CONFIG -= app_bundle

include(../../../src/IWebCore.pri)

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        DataBean.cpp \
        main.cpp \
        mysql/MySqlDb.cpp \
        mysql/MySqlModel.cpp \
        mysql/TestMySqlDb.cpp \
        sqlite/SqliteDb.cpp \
        sqlite/SqliteModel.cpp \
        sqlite/TestSqliteDb.cpp

RESOURCES += \
    res.qrc

DISTFILES += \
    config.json

HEADERS += \
    DataBean.h \
    mysql/MySqlDb.h \
    mysql/MySqlModel.h \
    mysql/TestMySqlDb.h \
    sqlite/SqliteDb.h \
    sqlite/SqliteModel.h \
    sqlite/TestSqliteDb.h
