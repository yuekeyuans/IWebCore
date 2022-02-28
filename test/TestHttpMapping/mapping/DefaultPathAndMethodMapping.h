#pragma once

#include <QtCore>
#include <IWebCore>

class DefaultPathAndMethodMapping : public IControllerInterface<DefaultPathAndMethodMapping, true>
{
    Q_GADGET
    $AsController(DefaultPathAndMethodMapping, defaultPath)

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
