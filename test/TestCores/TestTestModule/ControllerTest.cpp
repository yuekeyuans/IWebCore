#include "HTTPRequest.hpp"
#include "ControllerTest.h"
#include <QtTest>

ControllerTest::ControllerTest()
{
}

// TODO: crash does no matter, because it is the test.
void ControllerTest::a()
{
//    try
//    {
        http::Request request{"http://127.0.0.1:8550/test"};
        const auto response = request.send("GET");
        auto data = QString::fromStdString(std::string{response.body.begin(), response.body.end()}); // print the result
        QVERIFY(data == "hello world");
//    }
//    catch (const std::exception& e)
//    {
//        qDebug() << "Request failed, error: " << e.what() << '\n';
//    }
}
