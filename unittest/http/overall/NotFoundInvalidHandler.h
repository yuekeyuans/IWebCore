#pragma once

#include "http/invalid/IHttpInvalidHandlerInterface.h"
#include "http/invalid/IHttpNotFoundInvalid.h"

using namespace IWebCore;

class NotFoundInvalidHandler : public ITaskWareUnit<NotFoundInvalidHandler, IHttpTaskCatagory>
        //public IHttpInvalidHandlerInterface<NotFoundInvalidHandler, IHttpNotFoundInvalid, true>
{
public:
    NotFoundInvalidHandler();

    virtual void $task(){
        qDebug() << "task run";
    }

public:
    virtual void handle(IRequest&) const;
};

