#include "ISessionController.h"

ISessionController::ISessionController()
{

}

QString ISessionController::testSession(ISessionJar &session)
{
    qDebug() << session.isValid();
    return "hello world";
}
