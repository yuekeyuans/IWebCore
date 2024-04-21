#pragma once

#include <IWeb/IControllerInterface>

class DefaultPathAndMethodMapping : public IHttpControllerInterface<DefaultPathAndMethodMapping, true>
{
    Q_GADGET
    $AsController(defaultPath)
public:
    DefaultPathAndMethodMapping();

    $GetMapping(get)
    QString get();

    $PostMapping(post)
    QString post();

    $PutMapping(put)
    QString put();

    $DeleteMapping(deletes)
    QString deletes();
};
