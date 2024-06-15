#pragma once

#include <IHttp/IHttpTestInterface>

class TestFormDataController : public IHttpTestInterface<TestFormDataController>
{
    Q_OBJECT
public:
    TestFormDataController() = default;

//private slots:
    void testPostFormData();
    void testPostLargeFile();

private slots:
    void testMultiPart();
};

