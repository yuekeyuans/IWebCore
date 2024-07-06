#include "core/util/IConvertUtil2.h"

$PackageWebCoreBegin

namespace IConvertUtil2{

    template<>
    IResult<bool> convertTo<bool>(const QString& value){
        return {value == "true", true};
    }
}

$PackageWebCoreEnd
