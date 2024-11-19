QT += core network xml

QT -= gui

CONFIG += c++14 console
CONFIG -= app_bundle

include(../../src/IWebCore.pri)

#QMAKE_CXXFLAGS += /MP

INCLUDEPATH += E:/project/libs/boost/boost_1_77_0/

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        main.cpp \
        mapping/ByteArrayReturnController.cpp \
        mapping/DefaultPathAndMethodMapping.cpp \
        mapping/HttpReturnController.cpp \
        mapping/JsonReturnController.cpp \
        mapping/PostMultiPartController.cpp \
        mapping/PostParameterController.cpp \
        mapping/PostRawDataController.cpp \
        mapping/PostTextParameterRequest.cpp \
        mapping/RedirectController.cpp \
        mapping/TestBean.cpp \
        mapping/TextReturnController.cpp \
        mapping/XmlParameterController.cpp \
        plugins/Status404Page.cpp \
        urlPattern/UrlPatternController.cpp \
        urlPattern/UrlPatternController2.cpp

QMAKE_CXXFLAGS_RELEASE += -O3       # Release -O3

RESOURCES += \
    resource.qrc

HEADERS += \
    mapping/ByteArrayReturnController.h \
    mapping/DefaultPathAndMethodMapping.h \
    mapping/HttpReturnController.h \
    mapping/JsonReturnController.h \
    mapping/PostMultiPartController.h \
    mapping/PostParameterController.h \
    mapping/PostRawDataController.h \
    mapping/PostTextParameterRequest.h \
    mapping/RedirectController.h \
    mapping/TestBean.h \
    mapping/TextReturnController.h \
    mapping/XmlParameterController.h \
    plugins/Status404Page.h \
    urlPattern/UrlPatternController.h \
    urlPattern/UrlPatternController2.h
