#pragma once

#include "core/task/default/IInitializationTaskInterface.h"

class IHttpControllerParameterTask : public IInitializationTaskInterface<IHttpControllerParameterTask>
{
public:
    IHttpControllerParameterTask();

public:
    virtual void $task() final;
};

