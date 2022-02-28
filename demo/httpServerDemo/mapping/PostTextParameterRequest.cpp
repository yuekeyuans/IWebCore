#include "PostTextParameterRequest.h"

PostTextParameterRequest::PostTextParameterRequest()
{
    $ConstructController
}

QString PostTextParameterRequest::postText6($Body (qlonglong, value))
{
    qDebug() << value_bodyContent;
    return IConvertUtil::toString(value_bodyContent);
}

QString PostTextParameterRequest::postText5($Body(QJsonValue, value))
{
    qDebug() << value_bodyContent;
    return IConvertUtil::toString(value_bodyContent);
}

QString PostTextParameterRequest::postText4($Body (QJsonObject, value))
{
    qDebug() << value_bodyContent;
    return IConvertUtil::toString(value_bodyContent);
}

QString PostTextParameterRequest::postText3($Body (double, value))
{
    qDebug() << value_bodyContent;
    return IConvertUtil::toString(value_bodyContent, 'g', 10);
}

QString PostTextParameterRequest::postTextPlain($Body (QString, name))
{
    qDebug() << name_bodyContent;
    return name_bodyContent;
}

QString PostTextParameterRequest::postText2($Body (int, value))
{
    qDebug() << value_bodyContent;
    return QString::number(value_bodyContent);
}
