#include "PostParameterController.h"

PostParameterController::PostParameterController() : IHttpControllerInterface()
{
}

QString PostParameterController::p1(IRequest &request, IResponse &response)
{
    response.setMime(IHttpMime::TEXT_CSS);
    response.setStatus(IHttpStatus::GONE_410);
    return request.url();
}

QString PostParameterController::p2(IRequest &request)
{
    bool ok;
    QString val1 = request.getParameter(QStringLiteral("岳克远"), ok);
    QString val2 = request.getParameter(QStringLiteral("岳飞"), ok);
    qDebug() << "p2" << val1 << val2;
    return val1 + val2;
}

QString PostParameterController::p3(IRequest &request)
{
    bool ok;
    QString val1 = request.getParameter(QStringLiteral("岳克远"), ok);

    QString val2 = request.getParameter(QStringLiteral("岳飞"), ok);
    return val1 + val2;
}

QString PostParameterController::p4($Content (QJsonValue, value))
{
    qDebug() << value_content;
    return IJsonUtil::toString(value_content);
}

QString PostParameterController::p5($Content (QJsonObject, value))
{
    qDebug() << value_content;
    return IJsonUtil::toString(value_content);
}

QString PostParameterController::p6($Content (QJsonArray, value))
{
    qDebug() << value_content;
    return IJsonUtil::toString(value_content);
}

QString PostParameterController::p7($Content (QJsonArray, value))
{
    qDebug() << value_content;
    return IJsonUtil::toString(value_content);
}

QString PostParameterController::p8($Content (QJsonValue&, value))
{
    qDebug() <<value_content;
    return IJsonUtil::toString(value_content);
}

QString PostParameterController::p9($Body (int&, name))
{
    qDebug() <<name_body;
    return QString::number(name_body);
}

QString PostParameterController::p10($Body (QString, name))
{
    qDebug() <<name_body;
    return name_body;
}

QString PostParameterController::p11($Body (bool, name))
{
    qDebug() <<name_body;
    return IConvertUtil::toString(name_body);
}

QString PostParameterController::p12($Body (double, name))
{
    qDebug() <<name_body;
    return QString::number(name_body);
}

QString PostParameterController::p13($Body (QJsonArray, name))
{
    qDebug() <<name_body;
    return IConvertUtil::toString(name_body);
}

QString PostParameterController::p14($Body (QJsonObject, name))
{
    qDebug() << name_body;
    return IConvertUtil::toString(name_body);
}
