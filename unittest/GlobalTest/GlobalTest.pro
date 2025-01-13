QT -= gui

CONFIG += c++17 console
CONFIG -= app_bundle

#CONFIG += console release  # 允许在 release 模式下输出到控制台
#CONFIG -= app_bundle       # 禁用 Windows GUI 应用，仅控制台
#DEFINES += QT_MESSAGELOGCONTEXT  # 保留文件名、行号等上下文信息
#QMAKE_CXXFLAGS_RELEASE += -Zi  # 生成 PDB 调试符号
#QMAKE_LFLAGS_RELEASE += /DEBUG  # 保留 PDB 调试符号文件
#LIBS += -ldbghelp  # 链接 dbghelp 库以支持 MiniDump

include(../../src/IWebCore.pri)

DEFINES += QMAKE_PROJECT_DIR=\\\"$$PWD\\\"
SOURCES += \
        TempUnitTest.cpp \
        bean/StudentBean.cpp \
        controller/Argument/BasicArgument.cpp \
        controller/ContentController.cpp \
        controller/UrlController.cpp \
        controller/returnType/ReturnTypeController.cpp \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    TempUnitTest.h \
    bean/StudentBean.h \
    controller/Argument/BasicArgument.h \
    controller/ContentController.h \
    controller/UrlController.h \
    controller/returnType/ReturnTypeController.h
