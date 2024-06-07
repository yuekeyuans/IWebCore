#include "TestFormDataController.h"
#include <iostream>

void TestFormDataController::testPostFormData()
{
    ICurlResponse response = ICurl("http://127.0.0.1:8550/postData")
            .withPostData("{\"foo\": 1, \"bar\": \"baz\"}")
            .withHeaderContentType("application/json")
            .execPost();
    qDebug() << response.m_status;
}
