#include "TestInvalid.h"

TestInvalid::TestInvalid(const QString &description)
    :IHttpInvalidInterface(IHttpStatus::Code::ACCEPTED_202, description)
{
}
