#include "HTTPRequest.hpp"
#include "ControllerTest.h"
#include <winsock2.h> // 对于 Windows 平台
#include <iostream>

ControllerTest::ControllerTest()
{
}

void ControllerTest::a()
{
    try
    {
        // you can pass http::InternetProtocol::V6 to Request to make an IPv6 request
        http::Request request{"http://www.baidu.com"};

        // send a get request
        const auto response = request.send("GET");
        std::cout << std::string{response.body.begin(), response.body.end()} << '\n'; // print the result
    }
    catch (const std::exception& e)
    {
        qDebug() << "Request failed, error: " << e.what() << '\n';
    }
}
