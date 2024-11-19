#include "PostRawDataController.h"

PostRawDataController::PostRawDataController()
{
}

QString PostRawDataController::rawData1($Content (QByteArray, raw))
{
    qDebug() << raw_content;
    return QString(raw_content);
}
