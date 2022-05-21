#include "IAstInfo.h"

$PackageWebCoreBegin

IAstInfo::operator QString() const
{
    QString ret;
    if(!file.isEmpty()){
        ret.append(" [FILE] ").append(file);
    }
    if(!className.isEmpty()){
        ret.append(" [CLASSNAME] ").append(className);
    }
    if(!function.isEmpty()){
        ret.append(" [FUNCTION] ").append(function);
    }
    if(line != INT_MIN){
        ret.append(" [LINE] ").append(QString::number(line));
    }
    if(!returnType.isEmpty()){
        ret.append(" [RETURN_TYPE] ").append(returnType);
    }
    if(!paramterType.isEmpty()){
        ret.append(" [PARAMETER_TYPE] ").append(paramterType);
    }
    if(!parameterName.isEmpty()){
        ret.append(" [PARAMETER_NAME] ").append(parameterName);
    }

    return ret;
}

$PackageWebCoreEnd
