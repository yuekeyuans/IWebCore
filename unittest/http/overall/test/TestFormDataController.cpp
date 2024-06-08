#include "TestFormDataController.h"
#include <iostream>

void TestFormDataController::testPostFormData()
{
    auto curl = ICurl("http://127.0.0.1:8550/postData")
            .withPostData(R"({"foo": 1, "bar": "baz"})")
            .withHeaderContentType("application/json");
    auto response = curl.execPost();
    qDebug() << response.m_status << response.m_body;
}

void TestFormDataController::testPostLargeFile()
{
    ICurlResponse response = ICurl("http://127.0.0.1:8550/postData")
            .withPostDataFile("D:/yuekeyuan.pdf")
            .execPost();
    qDebug() << response.m_status << response.m_body;
}
