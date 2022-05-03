#include "IBeanPostController.h"

IBeanPostController::IBeanPostController()
{

}

QString IBeanPostController::postMixed1(IRequest &request, UserBean bean)
{
    qDebug() << IHttpMimeHelper::toString(request.mime());
    qDebug() << bean;
    return bean;
}

QString IBeanPostController::postMixed2(IRequest &request, UserBean bean)
{
    qDebug() << IHttpMimeHelper::toString(request.mime());
    qDebug() << bean;
    return bean;
}

QString IBeanPostController::postJsonValue(IRequest &request, $Content (UserBean, bean))
{
    qDebug() << IHttpMimeHelper::toString(request.mime());
    qDebug() << bean_content;
    return bean_content;
}

QString IBeanPostController::postUrlEncoded(IRequest &request, $Content (UserBean, bean))
{
    qDebug() << IHttpMimeHelper::toString(request.mime());
    qDebug() << bean_content;
    return bean_content;
}

QString IBeanPostController::postMultiPart(IRequest &request, $Content (UserBean, bean))
{
    qDebug() << IHttpMimeHelper::toString(request.mime());
    qDebug() << bean_content;
    return bean_content;
}
