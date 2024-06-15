#include "FormDataController.h"
#include "http/net/impl/IRequestRaw.h"

FormDataController::FormDataController()
{

}

QString FormDataController::postData(IRequest &request)
{
    qDebug().noquote() << "body length" << request.getRaw()->m_requestBody.length();
    return "hello world";
}
