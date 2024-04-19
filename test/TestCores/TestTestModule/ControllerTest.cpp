#include "HTTPRequest.hpp"
#include "ControllerTest.h"
#include <winsock2.h> // 对于 Windows 平台
#include <iostream>
#include <QtTest>

ControllerTest::ControllerTest()
{
}

void ControllerTest::a()
{
    try
    {
        // you can pass http::InternetProtocol::V6 to Request to make an IPv6 request
        http::Request request{"http://127.0.0.1:8550/test"};
        // send a get request
        const auto response = request.send("GET");
        auto data = QString::fromStdString(std::string{response.body.begin(), response.body.end()}); // print the result
        QVERIFY(data == "hello world");
    }
    catch (const std::exception& e)
    {
        qDebug() << "Request failed, error: " << e.what() << '\n';
    }
}
