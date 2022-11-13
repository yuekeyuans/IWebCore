#pragma once

#include <IWebCore>

class HeaderJarController : public IControllerInterface<HeaderJarController, true>
{
    Q_GADGET
    $AsController (HeaderJarController, header)
public:
    HeaderJarController() = default;

public:

    // test get
    $GetMapping (getHeaderJar)
    QString getHeaderJar(IHeaderJar jar);

    $GetMapping (testRequestHeaderKeys)
    QString testRequestHeaderKeys(const IHeaderJar& jar);

    $GetMapping (testAddResponseHeader)
    QString testAddResponseHeader(IHeaderJar& jar);
    // test set

};

