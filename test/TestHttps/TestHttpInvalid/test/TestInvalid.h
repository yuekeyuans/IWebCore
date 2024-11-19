#pragma once

#include <IWeb/IHttpInvalidInterface>

class TestInvalid : public IHttpInvalidInterface<TestInvalid>
{
public:
    TestInvalid(const QString& description="");
};

