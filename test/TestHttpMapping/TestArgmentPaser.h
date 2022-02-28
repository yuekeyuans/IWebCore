#pragma once

#include <IWebCore>

class TestArgmentPaser : public IArgumentParserInterface<TestArgmentPaser, false>
{
    $UseInstance(TestArgmentPaser)
public:
    TestArgmentPaser() = default;
    virtual void task(const QStringList &arguments) override;
};
