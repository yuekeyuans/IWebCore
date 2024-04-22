#pragma once

#include <IWebCore>

class FiveCharaterUrlValidator : public IHttpPathFunctorValidatorInterface<FiveCharaterUrlValidator>
{
public:
    FiveCharaterUrlValidator() = default;

public:
    virtual QString name() final;
    virtual Validator validator() final;

};
