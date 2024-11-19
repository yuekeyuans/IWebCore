QT -= gui


CONFIG += c++17 console
CONFIG -= app_bundle


include(../../../src/IWebCore.pri)

DEFINES += QT_DEPRECATED_WARNINGS

LIBS += -lws2_32

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        ControllerTest.cpp \
        FirstTest.cpp \
        TestController.cpp \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    ControllerTest.h \
    FirstTest.h \
    TestController.h
