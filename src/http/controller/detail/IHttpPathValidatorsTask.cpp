#include "IHttpPathValidatorsTask.h"
#include "http/IHttpManage.h"
#include "http/controller/IHttpPath.h"

$PackageWebCoreBegin

namespace detail {
    static bool isShortValue(const QString& value);
    static bool isUShortValue(const QString& value);
    static bool isIntValue(const QString& value);
    static bool isUIntValue(const QString& value);
    static bool isLongValue(const QString& value);
    static bool isULongValue(const QString& value);
    static bool isLongLongValue(const QString& value);
    static bool isULongLongValue(const QString& value);
    static bool isFloatValue(const QString& value);
    static bool isDoubleValue(const QString& value);
    static bool isQDateValue(const QString& value);
    static bool isQTimeValue(const QString& value);
    static bool isQDateTimeValue(const QString& value);
    static bool isQStringValue(const QString& value);
}

void IHttpPathValidatorsTask::$task()
{
    QMap<QString, QString> validatorRegMap = {
        {"uuid",    "^[0-9a-f]{8}(-[0-9a-f]{4}){3}-[0-9a-f]{12}$"},
        {"base64",  "^[a-zA-Z0-9+/]*={0,2}$"},
    };

    QMap<QString, IHttpPathFragment::Validator> validatorFunMap = {
        {"short", detail::isShortValue},
        {"ushort", detail::isUShortValue},
        {"int", detail::isIntValue},
        {"uint", detail::isUIntValue},
        {"long", detail::isLongValue},
        {"ulong", detail::isULongValue},
        {"longlong", detail::isLongLongValue},
        {"ulonglong", detail::isULongLongValue},
        {"float", detail::isFloatValue},
        {"double", detail::isDoubleValue},

        {"date", detail::isQDateValue},
        {"QDate", detail::isQDateValue},
        {"time", detail::isQTimeValue},
        {"QTime", detail::isQTimeValue},
        {"datetime", detail::isQDateTimeValue},
        {"QDateTime", detail::isQDateTimeValue},

        {"string", detail::isQStringValue},
        {"QString", detail::isQStringValue},
    };

    for(auto key : validatorRegMap){
        QRegularExpression exp(validatorRegMap[key]);
        IHttpManage::instance()->registerPathValidator(key, [=](const QString& value)->bool{
            return exp.match(value).hasMatch();
        });
    }
    for(auto key : validatorFunMap.keys()){
        IHttpManage::instance()->registerPathValidator(key, validatorFunMap[key]);
    }
}

bool detail::isShortValue(const QString& value){
    bool ok;
    value.toShort(&ok);
    return ok;
}

bool detail::isUShortValue(const QString& value){
    bool ok;
    value.toUShort(&ok);
    return ok;
}

bool detail::isIntValue(const QString& value){
    bool ok;
    value.toInt(&ok);
    return ok;
}

bool detail::isUIntValue(const QString& value){
    bool ok;
    value.toUInt(&ok);
    return ok;
}

bool detail::isLongValue(const QString& value){
    bool ok;
    value.toLong(&ok);
    return ok;
}

bool detail::isULongValue(const QString& value){
    bool ok;
    value.toULong(&ok);
    return ok;
}

bool detail::isLongLongValue(const QString& value){
    bool ok;
    value.toLongLong(&ok);
    return ok;
}

bool detail::isULongLongValue(const QString& value){
    bool ok;
    value.toULongLong(&ok);
    return ok;
}

bool detail::isFloatValue(const QString& value){
    bool ok;
    value.toFloat(&ok);
    return ok;
}

bool detail::isDoubleValue(const QString& value){
    bool ok;
    value.toDouble(&ok);
    return ok;
}

bool detail::isQDateValue(const QString& value){
    QVariant variant = value;
    return variant.toDate().isValid();
}

bool detail::isQTimeValue(const QString& value){
    QVariant variant = value;
    return variant.toTime().isValid();
}

bool detail::isQDateTimeValue(const QString& value){
    QVariant variant = value;
    return variant.toDateTime().isValid();
}

bool detail::isQStringValue(const QString& value){
    return !value.isEmpty();
}

$PackageWebCoreEnd
