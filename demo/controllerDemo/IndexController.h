#pragma once

#include <IWebCore.h>

class IndexController : public IControllerInterface
{
    Q_GADGET
    $Controller(IndexController)

public:
    IndexController();

    $GetMapping(index)
    void index();

    $GetMapping(indexPage, /index)
    void indexPage();

};

$RegisterController(IndexController)
