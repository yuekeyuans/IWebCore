#include "RequestParameterController.h"

QString RequestParameterController::fun1(IStringView $Body(data))
{
    return data.toQString();
}
