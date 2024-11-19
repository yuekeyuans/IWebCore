#pragma once

#include <QtCore>
#include <IWebCore>

class RedirectController : public IControllerInterface
{
    Q_GADGET
    $AsController(RedirectController)
public:
    RedirectController();

    $GetMapping(redirect1, redirect1)
    IRedirectResponse redirect1();

    $GetMapping(redirect2, redirect2)
    QString redirect2();

    $GetMapping(redirect3, redirect3)
    IRedirectResponse redirect3();

    $GetMapping(redirect4, redirect4)
    IRedirectResponse redirect4();

    $GetMapping(redirect5, redirect5)
    IJsonResponse redirect5();

};

$RegisterController(RedirectController)

