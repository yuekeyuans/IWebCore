#include "TestFormDataController.h"
#include <iostream>

void TestFormDataController::testPostFormData()
{
    auto curl = ICurl("/postData")
            .withPostData(R"({"foo": 1, "bar": "baz"})")
            .withHeaderContentType("application/json");
    auto response = curl.execPost();
    qDebug() << response.m_status << response.m_body;
}

void TestFormDataController::testPostLargeFile()
{
    ICurlResponse response = ICurl("/postData")
            .withPostDataFile("D:/yuekeyuan.pdf", "application/pdf")
            .execPost();
    qDebug() << response.m_status << response.m_body;
}
