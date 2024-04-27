#pragma once

#include <IWeb/IHttpTestInterface>

class InvalidControllerTest : public IHttpTestInterface<InvalidControllerTest>
{
    Q_OBJECT
public:
    InvalidControllerTest() = default;

private slots:
    void testInvalid();
};

