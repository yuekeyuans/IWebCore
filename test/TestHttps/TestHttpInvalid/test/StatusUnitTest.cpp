#include "StatusUnitTest.h"
#include "IWeb/IHttpInvalidInterface"
#include "http/response/IByteArrayResponse.h"

class NameInvalid : public IHttpInvalidInterface<NameInvalid>
{
public:
    NameInvalid(const QString& description = "") : IHttpInvalidInterface(IHttpStatus::INTERNAL_SERVER_ERROR_500, description)
    {
    }
};

void StatusUnitTest::slotTestInterface()
{
    NameInvalid invalid;
    qDebug() << invalid.status << invalid.description << invalid.tag;
    QVERIFY(invalid.status == IHttpStatus::INTERNAL_SERVER_ERROR_500);
    QVERIFY(invalid.description.isEmpty());
    QVERIFY(invalid.tag == "NameInvalid");
}

void StatusUnitTest::slotTestOperatorRef()
{
    IByteArrayResponse response;
    response["hello"] = "world";
    qDebug() << response["hello"];
}
