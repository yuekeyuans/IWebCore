#pragma once

#include <IWebCore>

class FiveCharaterUrlValidator : public IHttpPathRegexpValidatorInterface<FiveCharaterUrlValidator>
{
public:
    FiveCharaterUrlValidator() = default;
    virtual void task() override;
};
