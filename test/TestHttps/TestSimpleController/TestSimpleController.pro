QT -= gui

CONFIG += c++17 console /utf-8 /utf8
CONFIG -= app_bundle

include(../../../src/IWebCore.pri)

DEFINES += QT_DEPRECATED_WARNINGS

DEFINES += USE_INLINE

SOURCES += \
        TestController.cpp \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    TestController.h

RESOURCES += \
    resource.qrc
