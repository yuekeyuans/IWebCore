#pragma once

#include <IHttp/IHttpControllerInterface>

using namespace IWebCore;

class FormDataController : public IHttpControllerInterface<FormDataController>
{
    Q_GADGET
public:
    FormDataController();

public:
    $PostMapping(postData, postData)
    QString postData(IRequest& request);
};

