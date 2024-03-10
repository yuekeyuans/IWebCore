#include "IControllerPathValidatorTask.h"
#include "web/controller/IControllerManage.h"

$PackageWebCoreBegin

namespace IControllerPathValidatorTaskHelper {
    bool isShortValue(const QString& value);
    bool isUShortValue(const QString& value);
    bool isIntValue(const QString& value);
    bool isUIntValue(const QString& value);
    bool isLongValue(const QString& value);
    bool isULongValue(const QString& value);
    bool isLongLongValue(const QString& value);
    bool isULongLongValue(const QString& value);
    bool isFloatValue(const QString& value);
    bool isDoubleValue(const QString& value);
    bool isQDateValue(const QString& value);
    bool isQTimeValue(const QString& value);
    bool isQDateTimeValue(const QString& value);
    bool isQStringValue(const QString& value);
}

void IControllerPathValidatorTask::task()
{
    static QMap<QString, QString> validatorRegMap = {
        {"uuid",    "^[0-9a-f]{8}(-[0-9a-f]{4}){3}-[0-9a-f]{12}$"},
        {"base64",  "^[a-zA-Z0-9+/]*={0,2}$"},
    };

    using ValidatorFun = bool (*)(const QString&);
    static QMap<QString, ValidatorFun> validatorFunMap = {
        {"short", IControllerPathValidatorTaskHelper::isShortValue},
        {"ushort", IControllerPathValidatorTaskHelper::isUShortValue},
        {"int", IControllerPathValidatorTaskHelper::isIntValue},
        {"uint", IControllerPathValidatorTaskHelper::isUIntValue},
        {"long", IControllerPathValidatorTaskHelper::isLongValue},
        {"ulong", IControllerPathValidatorTaskHelper::isULongValue},
        {"longlong", IControllerPathValidatorTaskHelper::isLongLongValue},
        {"ulonglong", IControllerPathValidatorTaskHelper::isULongLongValue},
        {"float", IControllerPathValidatorTaskHelper::isFloatValue},
        {"double", IControllerPathValidatorTaskHelper::isDoubleValue},

        {"date", IControllerPathValidatorTaskHelper::isQDateValue},
        {"QDate", IControllerPathValidatorTaskHelper::isQDateValue},
        {"time", IControllerPathValidatorTaskHelper::isQTimeValue},
        {"QTime", IControllerPathValidatorTaskHelper::isQTimeValue},
        {"datetime", IControllerPathValidatorTaskHelper::isQDateTimeValue},
        {"QDateTime", IControllerPathValidatorTaskHelper::isQDateTimeValue},

        {"string", IControllerPathValidatorTaskHelper::isQStringValue},
        {"QString", IControllerPathValidatorTaskHelper::isQStringValue},
    };

    for(auto key : validatorRegMap.keys()){
        IControllerManage::instance()->registerPathValidator(key, validatorRegMap[key]);
    }

    for(auto key : validatorFunMap.keys()){
        IControllerManage::instance()->registerPathValidator(key, validatorFunMap[key]);
    }
}

bool IControllerPathValidatorTaskHelper::isShortValue(const QString& value){
    bool ok;
    value.toShort(&ok);
    return ok;
}

bool IControllerPathValidatorTaskHelper::isUShortValue(const QString& value){
    bool ok;
    value.toUShort(&ok);
    return ok;
}

bool IControllerPathValidatorTaskHelper::isIntValue(const QString& value){
    bool ok;
    value.toInt(&ok);
    return ok;
}

bool IControllerPathValidatorTaskHelper::isUIntValue(const QString& value){
    bool ok;
    value.toUInt(&ok);
    return ok;
}

bool IControllerPathValidatorTaskHelper::isLongValue(const QString& value){
    bool ok;
    value.toLong(&ok);
    return ok;
}

bool IControllerPathValidatorTaskHelper::isULongValue(const QString& value){
    bool ok;
    value.toULong(&ok);
    return ok;
}

bool IControllerPathValidatorTaskHelper::isLongLongValue(const QString& value){
    bool ok;
    value.toLongLong(&ok);
    return ok;
}

bool IControllerPathValidatorTaskHelper::isULongLongValue(const QString& value){
    bool ok;
    value.toULongLong(&ok);
    return ok;
}

bool IControllerPathValidatorTaskHelper::isFloatValue(const QString& value){
    bool ok;
    value.toFloat(&ok);
    return ok;
}

bool IControllerPathValidatorTaskHelper::isDoubleValue(const QString& value){
    bool ok;
    value.toDouble(&ok);
    return ok;
}

bool IControllerPathValidatorTaskHelper::isQDateValue(const QString& value){
    QVariant variant = value;
    return variant.toDate().isValid();
}

bool IControllerPathValidatorTaskHelper::isQTimeValue(const QString& value){
    QVariant variant = value;
    return variant.toTime().isValid();
}

bool IControllerPathValidatorTaskHelper::isQDateTimeValue(const QString& value){
    QVariant variant = value;
    return variant.toDateTime().isValid();
}

bool IControllerPathValidatorTaskHelper::isQStringValue(const QString& value){
    return !value.isEmpty();
}

$PackageWebCoreEnd
