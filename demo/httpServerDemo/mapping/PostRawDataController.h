#pragma once

#include <IWebCore>

// used for accept raw data
class PostRawDataController : public IControllerInterface
{
    Q_GADGET
    $AsController(PostRawDataController)
public:
    PostRawDataController();

    $PostMapping(rawData1, /rawData1)
    QString rawData1($Body(QByteArray, raw));

};

$RegisterController(PostRawDataController)
