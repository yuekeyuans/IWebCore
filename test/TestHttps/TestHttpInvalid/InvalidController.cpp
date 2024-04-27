#include "InvalidController.h"
#include "test/TestInvalid.h"

QString InvalidController::testInvalid(IRequest &request)
{
    request.setInvalid(TestInvalid("testInvalid"));
    return {};
}
