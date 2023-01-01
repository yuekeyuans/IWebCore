#pragma once

#include <IWebCore>

class ISessionController : public IControllerInterface<ISessionController>
{
    Q_GADGET
    $AsController(ISessionController)
public:
    ISessionController();

    $GetMapping(testSession)
    QString testSession(ISessionJar& session);
};

