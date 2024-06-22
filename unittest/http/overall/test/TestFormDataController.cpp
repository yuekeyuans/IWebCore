#include "TestFormDataController.h"
#include <iostream>

void TestFormDataController::testPostFormData()
{
    auto curl = ICurl("/postData")
            .withJsonBody("({\"foo\": 1, \"bar\": \"bas\"})");
    auto response = curl.execPost();
    qDebug() << response.m_status << response.m_body;
}

void TestFormDataController::testPostLargeFile()
{
    auto file = createRandomFile();
    ICurlResponse response = ICurl("/postData")
            .withBinary(file)
            .execPost();
    qDebug() << response.m_status << response.m_body;
}

void TestFormDataController::testMultiPart()
{
    auto file = createRandomFile("abc.pdf");
    ICurlResponse response = ICurl("/postData")
            .withFormData("hello", "world")
            .withFormFile("file", file, "abc.pdf", "application/pdf")
            .execPost();
    qDebug() <<response.m_status << response.m_body;
}

void TestFormDataController::testJson()
{
    ICurlResponse response = ICurl("/postData")
            .withJsonBody(R"({"hello":"world"})")
            .execPost();
    qDebug() << response.m_status << response.m_body;
}
