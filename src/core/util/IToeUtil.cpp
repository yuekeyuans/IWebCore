#include "IToeUtil.h"
#include "IConstantUtil.h"

$PackageWebCoreBegin

inline void IToeUtil::setOk(bool &ok, bool value)
{
    ok = value;
}

inline void IToeUtil::setOk(bool *ok, bool value)
{
    if(ok != nullptr){
        *ok = value;
    }
}

inline void IToeUtil::setOk(bool condition, bool *ok, bool value)
{
    if(condition){
        if(ok != nullptr){
            *ok = value;
        }
    }
}

inline void IToeUtil::setOk(bool condition, bool &ok, bool value)
{
    if(condition){
        ok = value;
    }
}

inline void IToeUtil::setOkAnd(bool *ok, bool value)
{
    if(ok != nullptr){
        *ok &= value;
    }
}


inline void IToeUtil::setOkAnd(bool &ok, bool value)
{
    ok &= value;
}

inline bool IToeUtil::isPrimaryKeyType(QMetaType::Type type)
{
    static const QMetaType::Type PrimaryKeyTypes[4] = {QMetaType::Int, QMetaType::Long, QMetaType::LongLong, QMetaType::QString};
    const auto& pkTypes = PrimaryKeyTypes;
    auto it = std::find(std::begin(pkTypes), std::end(pkTypes), type);
    return it != std::end(pkTypes);
}

$PackageWebCoreEnd
