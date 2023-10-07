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


inline void IToeUtil::setOkOr(bool *ok, bool value)
{
    if(ok != nullptr){
        *ok |= value;
    }
}

inline void IToeUtil::setOkOr(bool &ok, bool value)
{
    ok |= value;
}

inline void IToeUtil::setOkXor(bool *ok, bool value)
{
    if(ok != nullptr){
        *ok ^= value;
    }
}

inline void IToeUtil::setOkXor(bool &ok, bool value)
{
    ok ^= value;
}

inline bool IToeUtil::isPrimaryKeyType(QMetaType::Type type)
{
    static const QMetaType::Type PrimaryKeyTypes[4] = {QMetaType::Int, QMetaType::Long, QMetaType::LongLong, QMetaType::QString};
    const auto& pkTypes = PrimaryKeyTypes;
    auto it = std::find(std::begin(pkTypes), std::end(pkTypes), type);
    return it != std::end(pkTypes);
}

// NOTE: this perhaps will be changed latter
inline bool IToeUtil::isFalsy(const QString &value)
{
    if(value.isNull() || value.trimmed().isEmpty()){
        return true;
    }
    static QStringList falsyArgs = {
        "NO", "N", "FALSE", "F", "0",
        "-0", "NULL", "NULLPTR",
        "UNDEFINED", "NAN", "FAIL",
    };
    return falsyArgs.contains(value.trimmed().toUpper());
}

inline bool IToeUtil::isTruthy(const QString &value)
{
    return !isFalsy(value);
}

inline QString IToeUtil::trimQuote(const QString &content)
{
    static const QString quote = "\\\"";

    if(content.startsWith(quote) && content.endsWith(quote)){
        return content.mid(2, content.length() - 4);
    }
    return content;
}

$PackageWebCoreEnd
