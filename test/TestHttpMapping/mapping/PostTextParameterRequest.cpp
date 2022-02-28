#include "PostTextParameterRequest.h"

PostTextParameterRequest::PostTextParameterRequest()
{
}

QString PostTextParameterRequest::postText6($Content (qlonglong, value))
{
    qDebug() << value_content;
    return IConvertUtil::toString(value_content);
}

QString PostTextParameterRequest::postText5($Content(QJsonValue, value))
{
    qDebug() << value_content;
    return IConvertUtil::toString(value_content);
}

QString PostTextParameterRequest::postText4($Content (QJsonObject, value))
{
    qDebug() << value_content;
    return IConvertUtil::toString(value_content);
}

QString PostTextParameterRequest::postText3($Content (double, value))
{
    qDebug() << value_content;
    return IConvertUtil::toString(value_content, 'g', 10);
}

QString PostTextParameterRequest::postTextPlain($Content (QString, name))
{
    qDebug() << name_content;
    return name_content;
}

QString PostTextParameterRequest::postText2($Content (int, value))
{
    qDebug() << value_content;
    return QString::number(value_content);
}
