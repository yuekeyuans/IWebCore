#pragma once

#include <IWebCore>

class HeaderJarController : public IControllerInterface<HeaderJarController, true>
{
    Q_GADGET
    $AsController (HeaderJarController, header)
public:
    HeaderJarController() = default;

public:
    $GetMapping (getHeaderJar)
    QString getHeaderJar(IHeaderJar jar);
};

