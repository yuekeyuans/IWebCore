#include "IBeanDateSerialize.h"

IJson IBeanDateSerialize::serialize(const void *ptr) const
{
    auto date = static_cast<const QDate*>(ptr);
    if(date->isNull() || !date->isValid()){
        return nullptr;
    }
    return date->toString("yyyy.MM.dd").toStdString();
}

bool IBeanDateSerialize::deserialize(void *ptr, const IJson &json) const
{
    auto datePtr = static_cast<QDate*>(ptr);
    if(json.is_null()){
        *datePtr = QDate{};
        return true;
    }
    auto date = QDate::fromString(QString::fromStdString(json.get<std::string>()), "yyyy.MM.dd");
    *datePtr = date;
    return true;
}
