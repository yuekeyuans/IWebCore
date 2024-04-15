#pragma once

#include <IWeb/IControllerInterface>

// used for accept raw data
class PostRawDataController : public IControllerInterface<PostRawDataController>
{
    Q_GADGET
    $AsController(PostRawDataController)
public:
    PostRawDataController();

    $PostMapping(rawData1, /rawData1)
    QString rawData1($Content(QByteArray, raw));

};

