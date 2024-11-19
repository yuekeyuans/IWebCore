#include "FiveCharaterUrlValidator.h"

QString FiveCharaterUrlValidator::marker() const
{
    return "5c";
}

FiveCharaterUrlValidator::Validator FiveCharaterUrlValidator::validator() const
{
    return [](const QString& data){
        return data.length() == 5;
    };
}
