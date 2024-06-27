#include "IGlobalAbort.h"

$PackageWebCoreBegin

QMap<int, QString> IGlobalAbort::abortDescription() const{
    return {
        {UnVisibleMethod, "this method must not be called at any time, but due to qt meta issue, this function must exist,"
                          "so the application abort this info."}
    };
}

QString IGlobalAbort::abortComment(){
    return "Abort about global fatal event";
}

$PackageWebCoreEnd
