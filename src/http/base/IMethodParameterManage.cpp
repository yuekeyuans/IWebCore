#include "IMethodParameterManage.h"

$PackageWebCoreBegin

#define PP_RegistBaseType(klassName)    \
    registCreateReturnFun(IMetaType(QMetaType:: ## klassName ), [](){  \
        return QMetaType::create(QMetaType:: ## klassName );   \
    }); \
    registDestroyReturnFun(IMetaType(QMetaType:: ## klassName ), [](void* ptr){    \
        QMetaType::destroy(QMetaType:: ## klassName , ptr);    \
    });


IMethodParameterManage::IMethodParameterManage()
{
    PP_RegistBaseType(QString)
    PP_RegistBaseType(QByteArray)
//    PP_RegistBaseType(Int)

//    registCreateReturnFun(IMetaType(QMetaType::QString), [](){
//        return QMetaType::create(QMetaType::QString);
//    });
//    registDestroyReturnFun(IMetaType(QMetaType::QString), [](void* ptr){
//        QMetaType::destroy(QMetaType::QString, ptr);
//    });
}

void IMethodParameterManage::registCreateReturnFun(IMetaType node, IMethodParameterManage::CreateReturnFun fun)
{
    m_createReturnFun[node] = fun;
}

void IMethodParameterManage::registDestroyReturnFun(IMetaType node, IMethodParameterManage::DestroyReturnFun fun)
{
    m_destroyReturnFun[node] = fun;
}

$PackageWebCoreEnd
