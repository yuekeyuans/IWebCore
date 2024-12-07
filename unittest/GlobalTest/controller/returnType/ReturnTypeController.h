#pragma once

#include <IHttp/IHttpControllerInterface>
#include "bean/StudentBean.h"
#include "http/response/IByteArrayResponse.h"
#include "http/response/IFileResponse.h"
#include "http/biscuits/IHttpHeader.h"
#include "http/invalid/IHttpBadRequestInvalid.h"
#include "http/response/IJsonResponse.h"

class ReturnTypeController : public IHttpControllerInterface<ReturnTypeController, true>
{
    Q_GADGET
    $AsController(ReturnTypeController)
public:
    ReturnTypeController();

public:
    $GetMapping(qstring)
    QString qstring(){
        return "QString";
    }

    $GetMapping(stdString)
    std::string stdString(){
        return "stdString";
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

    $GetMapping(getBeanList)
    IJsonResponse getBeanList(){
        return QList<StudentBean>{
            {},
            {}
        };
    }

    $GetMapping(fileResponse)
    IFileResponse fileResponse(){
        return "D:/elevoc_dnn_kernel.log";
    }
};

