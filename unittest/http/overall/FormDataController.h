#pragma once

#include <IHttp/IHttpControllerInterface>

class FormDataController : public IHttpControllerInterface<FormDataController, false>
{
    Q_GADGET
public:
    FormDataController() = default;

public:
    $PostMapping(postData, postData)
    QString postData(IRequest& request);
};

