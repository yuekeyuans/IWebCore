#include "IToeUtil.h"
#include "IConstantUtil.h"

$PackageWebCoreBegin

bool IToeUtil::isPrimaryKeyType(QMetaType::Type type)
{
    static const QMetaType::Type PrimaryKeyTypes[4] = {QMetaType::Int, QMetaType::Long, QMetaType::LongLong, QMetaType::QString};
    const auto& pkTypes = PrimaryKeyTypes;
    auto it = std::find(std::begin(pkTypes), std::end(pkTypes), type);
    return it != std::end(pkTypes);
}

// NOTE: this perhaps will be changed latter
bool IToeUtil::isFalsy(const QString &value)
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

bool IToeUtil::isTruthy(const QString &value)
{
    return !isFalsy(value);
}

/*!
 * \brief IToeUtil::trimQuote
 *
 * this is used for preprocessor mainly
 *
 * \param content
 * \return
 */
QString IToeUtil::trimQuote(const QString &content)
{
    static const QString quote = "\\\"";

    if(content.startsWith(quote) && content.endsWith(quote)){
        return content.mid(2, content.length() - 4);
    }
    return content;
}

$PackageWebCoreEnd
