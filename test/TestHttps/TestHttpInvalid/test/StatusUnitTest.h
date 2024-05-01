#pragma once

#include "ICore/IUnitTestInterface"

class StatusUnitTest : public IUnitTestInterface<StatusUnitTest, true>
{
    Q_OBJECT
public:
    StatusUnitTest() = default;

private slots:
    void slotTestInterface();
    void slotTestOperatorRef();
};

