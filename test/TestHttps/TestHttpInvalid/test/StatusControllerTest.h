#pragma once

#include "IWeb/IHttpTestInterface"

class StatusControllerTest : public IHttpTestInterface<StatusControllerTest>
{
    Q_OBJECT
public:
    StatusControllerTest() = default;

private slots:
    void testInt();
    void testIntString();
    void testStatus();
    void testStatusString();
    void testUserLiteral();

private:
    std::string url = "http://127.0.0.1:8550";
};

