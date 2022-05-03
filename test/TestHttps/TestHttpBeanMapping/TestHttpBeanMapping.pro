QT -= gui

QT += core network xml

CONFIG += c++11 console
CONFIG -= app_bundle


include(../../../src/IWebCore.pri)

DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        UserBean.cpp \
        controller/IBeanGetController.cpp \
        controller/IBeanPostController.cpp \
        controller/TableTestController.cpp \
        main.cpp \
        model/SqliteDb.cpp \
        model/UserModel.cpp \
        model/UserTable.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

HEADERS += \
    UserBean.h \
    controller/IBeanGetController.h \
    controller/IBeanPostController.h \
    controller/TableTestController.h \
    model/SqliteDb.h \
    model/UserModel.h \
    model/UserTable.h
