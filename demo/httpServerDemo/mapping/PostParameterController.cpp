#include "PostParameterController.h"

PostParameterController::PostParameterController() : IControllerInterface()
{
    $ConstructController
}

QString PostParameterController::p1(IRequest &request, IResponse &response)
{
    response.setMime(IHttpMime::TEXT_CSS);
    response.setStatus(IHttpStatus::GONE_410);
    return request.url();
}

QString PostParameterController::p2(IRequest &request)
{
    QString val1 = request.getParameter(QStringLiteral("岳克远"));
    QString val2 = request.getParameter(QStringLiteral("岳飞"));
    return val1 + val2;
}

QString PostParameterController::p3(IRequest &request)
{
    QString val1 = request.getParameter(QStringLiteral("岳克远"));
    QString val2 = request.getParameter(QStringLiteral("岳飞"));
    return val1 + val2;
}

QString PostParameterController::p4($Body (QJsonValue, value))
{
    qDebug() << value_bodyContent;
    return IJsonUtil::toString(value_bodyContent);
}

QString PostParameterController::p5($Body (QJsonObject, value))
{
    qDebug() << value_bodyContent;
    return IJsonUtil::toString(value_bodyContent);
}

QString PostParameterController::p6($Body (QJsonArray, value))
{
    qDebug() << value_bodyContent;
    return IJsonUtil::toString(value_bodyContent);
}

QString PostParameterController::p7($Body (QJsonArray, value))
{
    qDebug() << value_bodyContent;
    return IJsonUtil::toString(value_bodyContent);
}

QString PostParameterController::p8($Body (QJsonValue &, value))
{
    qDebug() <<value_bodyContent;
    return IJsonUtil::toString(value_bodyContent);
}

QString PostParameterController::p9($BodyVar (int, name))
{
    qDebug() <<name_body;
    return QString::number(name_body);
}

QString PostParameterController::p10($BodyVar (QString, name))
{
    qDebug() <<name_body;
    return name_body;
}

QString PostParameterController::p11($BodyVar (bool, name))
{
    qDebug() <<name_body;
    return IConvertUtil::toString(name_body);
}

QString PostParameterController::p12($BodyVar (double, name))
{
    qDebug() <<name_body;
    return QString::number(name_body);
}

QString PostParameterController::p13($BodyVar (QJsonArray, name))
{
    qDebug() <<name_body;
    return IConvertUtil::toString(name_body);
}

QString PostParameterController::p14($BodyVar (QJsonObject, name))
{
    qDebug() << name_body;
    return IConvertUtil::toString(name_body);
}
