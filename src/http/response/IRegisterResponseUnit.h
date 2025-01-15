//#pragma once

//#include "core/util/IHeaderUtil.h"
//#include "core/task/ITaskPreProcessor.h"

//$PackageWebCoreBegin
//// TODO: 这个文件优化掉，里面的东西放置在 detail 中
//template<typename T, bool enabled>
//class IRegisterResponseUnit
//{
//    $AsTaskUnit(IRegisterResponseUnit)
//public:
//    IRegisterResponseUnit() = default;
//};

//$UseTaskUnit(IRegisterResponseUnit)
//{
//    static std::once_flag flag;
//    std::call_once(flag, [](){
//        IResponseManage::instance()->registerResponse(IMetaUtil::getBareTypeName<T>(),
//                                                      ISingletonUnitDetail::getInstance<T>());
//    });
//}

//$PackageWebCoreEnd
