#pragma once
#include <QtCore>
#include <IWebCore.h>

class AdminController : IControllerInterface
{
    Q_GADGET
    $Controller(AdminController, admin)

public:
    AdminController();

    $GetMapping(admin)
    void admin();
};

$RegisterController(AdminController)



