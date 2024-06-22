#pragma once

#include <IHttp/IHttpControllerInterface>

using namespace IWebCore;

class FormDataController : public IHttpControllerInterface<FormDataController, false>
{
    Q_GADGET
public:
    FormDataController() = default;

public:
    $PostMapping(postData, postData)
    QString postData(IRequest& request);
};

