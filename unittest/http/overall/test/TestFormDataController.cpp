#include "TestFormDataController.h"
#include "HTTPRequest.hpp"
#include <iostream>

void TestFormDataController::testPostFormData()
{
    try
    {
        http::Request request{"http://127.0.0.1:8550/postData"};
        const std::string body = "{\"foo\": 1, \"bar\": \"baz\"}";
        const auto response = request.send("POST", body, {
            {"Content-Type", "application/json"}
        });

        qDebug() << QString::fromStdString(std::string{response.body.begin(), response.body.end()}) << '\n'; // print the result
    }
    catch (const std::exception& e)
    {
        qDebug() << e.what() << "wahtttttttt";
        std::cerr << "Request failed, error: " << e.what() << '\n';
    }
}
