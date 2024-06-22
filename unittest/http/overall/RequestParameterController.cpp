#include "RequestParameterController.h"

QString RequestParameterController::fun1($Body (IStringView, data))
{
    return data.toQString();
}
