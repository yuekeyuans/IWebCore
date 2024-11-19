#include <IWeb/HttpRequest>

#include "StatusControllerTest.h"
#include <iostream>

void StatusControllerTest::testInt()
{
    http::Request req(url + "/int");
    auto res = req.send("GET");
    QVERIFY(HttpRequestUtil::toBody(res).isEmpty());
    QVERIFY(HttpRequestUtil::toStatus(res) == IHttpStatusCode::NOT_FOUND_404);
}

void StatusControllerTest::testIntString()
{
    http::Request req(url + "/intString");
    auto res = req.send("GET");
    QVERIFY(HttpRequestUtil::toBody(res) == "status");
    QVERIFY(HttpRequestUtil::toStatus(res) == IHttpStatusCode::NOT_FOUND_404);
}

void StatusControllerTest::testStatus()
{
    http::Request req(url + "/status");
    auto res = req.send("GET");
    QVERIFY(HttpRequestUtil::toBody(res).isEmpty());
    QVERIFY(HttpRequestUtil::toStatus(res) == IHttpStatusCode::INTERNAL_SERVER_ERROR_500);
}

void StatusControllerTest::testStatusString()
{
    http::Request req(url + "/statusString");
    auto res = req.send("GET");
    QVERIFY(HttpRequestUtil::toBody(res) == "created");
    QVERIFY(HttpRequestUtil::toStatus(res) == IHttpStatusCode::CREATED_201);

}

void StatusControllerTest::testUserLiteral()
{
    http::Request req(url + "/userLiteral");
    auto res = req.send("GET");
    QVERIFY(HttpRequestUtil::toBody(res).isEmpty());
    QVERIFY(HttpRequestUtil::toStatus(res) == IHttpStatusCode::BAD_GATEWAY_502);
}

void StatusControllerTest::testReplace()
{
    http::Request req(url + "/replace");
    auto res = req.send("GET");
    QVERIFY(HttpRequestUtil::toBody(res) == "replace content");
    QVERIFY(HttpRequestUtil::toStatus(res) == IHttpStatusCode::NOT_FOUND_404);

}
