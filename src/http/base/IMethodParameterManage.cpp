#include "IMethodParameterManage.h"

$PackageWebCoreBegin

IMethodParameterManage::IMethodParameterManage()
{
    registCreateReturnFun(ITypeNode(QMetaType::QString), [](){
        return QMetaType::create(QMetaType::QString);
    });
    registDestroyReturnFun(ITypeNode(QMetaType::QString), [](void* ptr){
        QMetaType::destroy(QMetaType::QString, ptr);
    });
}

void IMethodParameterManage::registCreateReturnFun(ITypeNode node, IMethodParameterManage::CreateReturnFun fun)
{
    m_createReturnFun[node] = fun;
}

void IMethodParameterManage::registDestroyReturnFun(ITypeNode node, IMethodParameterManage::DestroyReturnFun fun)
{
    m_destroyReturnFun[node] = fun;
}

$PackageWebCoreEnd
