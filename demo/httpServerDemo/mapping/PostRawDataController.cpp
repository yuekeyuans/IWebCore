#include "PostRawDataController.h"

PostRawDataController::PostRawDataController()
{
    $ConstructController
}

QString PostRawDataController::rawData1($Body (QByteArray, raw))
{
    qDebug() << raw_bodyContent;
    return QString(raw_bodyContent);
}
