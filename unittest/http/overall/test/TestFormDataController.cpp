#include "TestFormDataController.h"
#include <iostream>

void TestFormDataController::testPostFormData()
{
    auto curl = ICurl("/postData")
            .withJsonBody(R"({\"foo\": 1, \"bar\": \"baz\"})");
    auto response = curl.execPost();
    qDebug() << response.m_status << response.m_body;
}

void TestFormDataController::testPostLargeFile()
{
    ICurlResponse response = ICurl("/postData")
            .withBinary("D:/yuekeyuan.pdf")
            .execPost();
    qDebug() << response.m_status << response.m_body;
}

void TestFormDataController::testMultiPart()
{
    ICurlResponse response = ICurl("/postData")
            .withFormData("hello", "world")
            .withFormFile("file", "D:/yuekeyuan.pdf", "yuekeyuan.pdf", "application/pdf")
            .execPost();
    qDebug() <<response.m_status << response.m_body;
}
