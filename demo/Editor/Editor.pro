QT       += core gui xml network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

include(../../src/src.pri)

SOURCES += \
    SideBar.cpp \
    main.cpp \
    MainWindow.cpp \
    orm/DictInfoTable.cpp \
    orm/SqliteDatabase.cpp

HEADERS += \
    MainWindow.h \
    SideBar.h \
    orm/DictInfoTable.h \
    orm/SqliteDatabase.h

FORMS += \
    MainWindow.ui \
    SideBar.ui

