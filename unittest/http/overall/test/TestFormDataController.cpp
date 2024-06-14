#include "TestFormDataController.h"
#include <iostream>

void TestFormDataController::testPostFormData()
{
    auto curl = ICurl("/postData")
            .withEncodeData(R"({"foo": 1, "bar": "baz"})")
            .withContentType(IHttpMime::APPLICATION_JSON);
    auto response = curl.execPost();
    qDebug() << response.m_status << response.m_body;
}

void TestFormDataController::testPostLargeFile()
{
    ICurlResponse response = ICurl("/postData")
            .withEncodeBinary("D:/yuekeyuan.pdf", "application/pdf")
            .execPost();
    qDebug() << response.m_status << response.m_body;
}

void TestFormDataController::testMultiPart()
{
}
