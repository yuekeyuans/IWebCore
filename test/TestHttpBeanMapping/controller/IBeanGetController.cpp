#include "IBeanGetController.h"

IBeanGetController::IBeanGetController()
{

}

QString IBeanGetController::getMixedBean1(UserBean bean)
{
    qDebug() << bean;
    return bean;
}

QString IBeanGetController::getUrlBean($Url (UserBean, bean))
{
    qDebug() << bean_url;
    return bean_url;
}

QString IBeanGetController::getParamBean($Param (UserBean, bean))
{
    qDebug() << bean_param;
    return bean_param;
}

QString IBeanGetController::getHeaderBean($Header (UserBean, bean))
{
    qDebug() << bean_header;
    return bean_header;
}
