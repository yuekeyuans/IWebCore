QT += testlib
QT += xml network sql
QT -= gui

include(../../../src/IWebCore.pri)

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  \
    MySqlWorldDatabase.cpp \
    MysqlDatabase.cpp \
    PhoneBean.cpp \
    PhoneModel.cpp \
    SqliteDatabase.cpp \
    SqliteModel.cpp \
    TestDatabase.cpp \
    TestOrm.cpp \
    TestOrmSelect.cpp \
    TestOrmUpdate.cpp \
    TestOrmUtil.cpp \
    TestSqliteOnlyDatbase.cpp \
    condition/ConditionBean.cpp \
    condition/TestConditionGroupBy.cpp \
    condition/TestConditionHaving.cpp \
    condition/TestConditionLimit.cpp \
    condition/TestConditionOrderBy.cpp \
    condition/TestConditionWhere.cpp \
    condition/TestOrmCondition.cpp \
    testMain.cpp \
    types/NumberBean.cpp \
    types/NumberModel.cpp \
    types/TestOrmBool.cpp \
    types/TestOrmDateTime.cpp \
    types/TestOrmNumber.cpp \
    types/TestOrmPrimaryKey.cpp \
    types/UserBean.cpp \
    types/UserModel.cpp \
    view/UserBeanView.cpp \
    world/CityModel.cpp \
    world/CityTable.cpp \
    world/CountryModel.cpp \
    world/CountryTable.cpp \
    world/LanguageModel.cpp \
    world/LanguageTable.cpp

HEADERS += \
    MySqlWorldDatabase.h \
    MysqlDatabase.h \
    PhoneBean.h \
    PhoneModel.h \
    SqliteDatabase.h \
    SqliteModel.h \
    TestDatabase.h \
    TestOrm.h \
    TestOrmSelect.h \
    TestOrmUpdate.h \
    TestOrmUtil.h \
    TestSqliteOnlyDatbase.h \
    condition/ConditionBean.h \
    condition/TestConditionGroupBy.h \
    condition/TestConditionHaving.h \
    condition/TestConditionLimit.h \
    condition/TestConditionOrderBy.h \
    condition/TestConditionWhere.h \
    condition/TestOrmCondition.h \
    types/NumberBean.h \
    types/NumberModel.h \
    types/TestOrmBool.h \
    types/TestOrmDateTime.h \
    types/TestOrmNumber.h \
    types/TestOrmPrimaryKey.h \
    types/UserBean.h \
    types/UserModel.h \
    view/UserBeanView.h \
    world/CityModel.h \
    world/CityTable.h \
    world/CountryModel.h \
    world/CountryTable.h \
    world/LanguageModel.h \
    world/LanguageTable.h
