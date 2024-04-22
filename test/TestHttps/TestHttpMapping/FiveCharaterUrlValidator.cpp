#include "FiveCharaterUrlValidator.h"

QString FiveCharaterUrlValidator::name()
{
    return "5c";
}

FiveCharaterUrlValidator::Validator FiveCharaterUrlValidator::validator()
{
    return [](const QString& data){
        return data.length() == 5;
    };
}
