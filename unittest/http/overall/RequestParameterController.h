﻿#pragma once

#include <IHttp/IHttpControllerInterface>

class RequestParameterController : public IHttpControllerInterface<RequestParameterController>
{
    Q_GADGET
    $AsController(/hello/)
public:
    RequestParameterController() = default;

    $GetMapping(fun1, fun1)
    QString fun1(std::pair<int, int> $Body(data)){
        return QString("hello world");
    }
};
