﻿#pragma once

#include <IHttp/IHttpControllerInterface>
#include "bean/StudentBean.h"
#include "http/response/IByteArrayResponse.h"
#include "http/response/IFileResponse.h"
#include "http/response/IPlainTextResponse.h"
#include "http/response/IRedirectResponse.h"
#include "http/biscuits/IHttpHeader.h"
#include "http/invalid/IHttpBadRequestInvalid.h"
#include "http/response/IJsonResponse.h"

class ReturnTypeController : public IHttpControllerInterface<ReturnTypeController, true>
{
    Q_GADGET
    $AsController(ReturnTypeController)
public:
    ReturnTypeController() = default;

public:
    $GetMapping(qstring)
    QString qstring(){
//        qDebug() << QThread::currentThreadId();
        return "QString";
    }

    $GetMapping(stdString)
    std::string stdString(){
        return "stdString";
    }

    $GetMapping(istring)
    IString istring(){
        IString a = "istring";
        return a;
    }

    $GetMapping(ijson)
    IJson ijson(){
        return IJson({"hello", "world"});
    }

// bytearray
    $GetMapping(qbytearray)
    QByteArray qbytearray(){
        return "QByteArray";
    }

    $GetMapping(iByteArarryResponse)
    IByteArrayResponse iByteArarryResponse(){
        return "IByteArrayResponse";
    }

    $GetMapping(iByteArarryResponse2)
    IByteArrayResponse iByteArarryResponse2(){
        IByteArrayResponse response2("iByteArarryResponse2");
        response2.setHeader(IHttpHeader::ContentType, IHttpMimeUtil::toString(IHttpMime::TEXT_PLAIN_UTF8));
        return response2;
    }

    $GetMapping(QStringofByteArraySuffix)
    QString QStringofByteArraySuffix(){
        return "$bytes:QStringofByteArraySuffix";
    }

    $GetMapping(testInvalid)
    IByteArrayResponse testInvalid(){
        return IHttpBadRequestInvalid("hello world");
    }

    $GetMapping(getBean)
    StudentBean getBean(){
        return {};
    }

    $GetMapping(getBeanQList)
    QList<StudentBean> getBeanQList()
    {
        return QList<StudentBean>{
            StudentBean{1, "hello"},
            StudentBean{2, "world"}
        };
    }

    $GetMapping(getBeanStdList)
    std::list<StudentBean> getBeanStdList()
    {
        return std::list<StudentBean>{
            StudentBean{1, "hello"},
            StudentBean{2, "world"}
        };
    }

    $GetMapping(getBeanQMapQstring)
    QMap<QString, StudentBean> getBeanQMapQstring()
    {
        return QMap<QString, StudentBean>{
            {"yue", StudentBean{1, "hello"}},
            {"qichu", StudentBean{2, "world"}}
        };
    }

    $GetMapping(getBeanList)
    IJsonResponse getBeanList(){
        return QList<StudentBean>{
            {},
            {}
        };
    }

    $GetMapping(fileResponse)
    IFileResponse fileResponse(){
        return ":/resource/defaultWebConfig.json";
    }

    $GetMapping(redirectResponse)
    IFileResponse redirectResponse(){
        return IRedirectResponse("https://www.baidu.com");
    }

    $GetMapping(cookieTest)
    IPlainTextResponse cookieTest(){
        IPlainTextResponse resp("hello world");
        resp.setHeader("hello", "world");
        resp.setCookie("name", "yuekeyuan");
        return resp;
    }
};

