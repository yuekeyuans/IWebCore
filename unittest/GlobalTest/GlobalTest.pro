QT -= gui

CONFIG += c++17 console
CONFIG -= app_bundle

include(../../src/IWebCore.pri)

DEFINES += QMAKE_PROJECT_DIR=\\\"$$PWD\\\"
SOURCES += \
        TempUnitTest.cpp \
        bean/StudentBean.cpp \
        controller/returnType/ReturnTypeController.cpp \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    TempUnitTest.h \
    bean/StudentBean.h \
    controller/returnType/ReturnTypeController.h