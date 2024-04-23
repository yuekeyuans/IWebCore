#pragma once

#include <IWebCore>

class FiveCharaterUrlValidator : public IHttpPathFunctorValidatorInterface<FiveCharaterUrlValidator>
{
public:
    FiveCharaterUrlValidator() = default;

public:
    virtual QString marker() const final;
    virtual Validator validator() const final;

};
