#pragma once

#include <IHttp/IHttpTestInterface>

class TestFormDataController : public IHttpTestInterface<TestFormDataController, false>
{
    Q_OBJECT
public:
    TestFormDataController() = default;

private slots:
    void testPostFormData();
    void testPostLargeFile();
    void testMultiPart();

private:
    void testJson();
};

