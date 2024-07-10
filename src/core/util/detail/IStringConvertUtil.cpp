//#include "core/util/IConvertUtil2.h"
//#include "core/base/IStringView.h"

//$PackageWebCoreBegin

//namespace IConvertUtil2{

//    template<>
//    IResult<bool> convertTo<bool>(const QString& value){
//        return {value == "true", true};
//    }
//    template<>
//    IResult<bool> convertTo<bool>(const char* value){
//        return convertTo<bool, QString>(value);
//    }
//    template<>
//    IResult<bool> convertTo<bool>(const QByteArray& data){
//        return convertTo<bool, QString>(data);
//    }
//    template<>
//    IResult<bool> convertTo<bool>(IStringView data){
//        return convertTo<bool, QString>(data.toQString());
//    }
//}

//$PackageWebCoreEnd
