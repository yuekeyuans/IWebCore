#include "core/base/IHeaderUtil.h"

$PackageWebCoreBegin

template<typename T>
class IRegisterResponseTypeUnit
{
public:
    IRegisterResponseTypeUnit() = default;

private:
    class IRegisterResponseTypeUnitPrivate{
    public:
        IRegisterResponseTypeUnitPrivate(){
            static std::once_flag flag;
            std::call_once(flag, [](){
                static T t;
                IResponseManage::registerResponseType(&t);
            });
        }
    };
    friend class IRegisterResponseTypeUnitPrivate;
    static IRegisterResponseTypeUnitPrivate m_IRegisterResponseTypeUnitPrivate;
    virtual void* IRegisterResponseTypeUnitPrivateTouch(){
        return &m_IRegisterResponseTypeUnitPrivate;
    }
}

template<typename T>
typename IResponseInterface<T>::IRegisterResponseTypeUnitPrivate
         IResponseInterface<T>::m_IRegisterResponseTypeUnitPrivate;

$PackageWebCoreEnd