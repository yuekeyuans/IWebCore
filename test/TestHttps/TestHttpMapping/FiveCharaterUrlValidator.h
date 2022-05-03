#pragma once

#include <IWebCore>

class FiveCharaterUrlValidator : public IControllerPathValidatorInterface<FiveCharaterUrlValidator>
{
    $UseInstance(FiveCharaterUrlValidator)
public:
    FiveCharaterUrlValidator() = default;
    virtual void task() override;
};
