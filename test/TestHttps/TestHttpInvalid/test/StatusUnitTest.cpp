#include "StatusUnitTest.h"
#include "IWeb/IHttpInvalidInterface"

class NameInvalid : public IHttpInvalidInterface<NameInvalid>
{
public:
    using IHttpInvalidInterface::IHttpInvalidInterface;
};

void StatusUnitTest::slotTestInterface()
{
    NameInvalid invalid(IHttpStatus::INTERNAL_SERVER_ERROR_500);
    qDebug() << invalid.status << invalid.description << invalid.tag << invalid.invalid;
    QVERIFY(invalid.status == IHttpStatus::INTERNAL_SERVER_ERROR_500);
    QVERIFY(invalid.description.isEmpty());
    QVERIFY(invalid.tag == "NameInvalid");
    QVERIFY(invalid.invalid = true);
}
