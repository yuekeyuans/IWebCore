#include "IBeanTypeCheckTask.h"
#include "core/bean/IBeanTypeManage.h"
#include "core/bean/IBeanAbort.h"

$PackageWebCoreBegin

void IBeanTypeCheckTask::task()
{
    const auto& propMap = IBeanTypeManage::instance()->m_propertiesMap;
    for(const std::pair<int, std::vector<QMetaProperty>>& pair : propMap){
//        auto id = pair.first;
        const std::vector<QMetaProperty>& props = pair.second;
        for(const auto& prop : props){
            checkPropertyType(prop);
        }
    }
}

double IBeanTypeCheckTask::order() const
{
    return 0;
}

void IBeanTypeCheckTask::checkPropertyType(const QMetaProperty &prop)
{
    static auto stdStringId = qMetaTypeId<std::string>();
    static std::vector<int> allowedTypes = {
        QMetaType::Bool, QMetaType::Char, QMetaType::UChar, QMetaType::SChar,
        QMetaType::Short, QMetaType::UShort, QMetaType::Int, QMetaType::UInt,
        QMetaType::Long, QMetaType::ULong, QMetaType::ULongLong, QMetaType::LongLong,
        QMetaType::Float, QMetaType::Double,
        QMetaType::QString, QMetaType::QStringList,
    };
    auto type = prop.userType();
    if(type == stdStringId){
        return;
    } else if(type >= QMetaType::User){
        if(!IBeanTypeManage::instance()->isBeanIdExist(type)){
            IBeanAbort::abortinvalid_bean_embended_type(QString("type: ") + QMetaType::typeName(type));
        }
    } else {
        if(std::find(allowedTypes.begin(), allowedTypes.end(), type) == allowedTypes.end()){
            IBeanAbort::abortinvalid_bean_field_type(QString("type: ") + QMetaType::typeName(type));
        }
    }
}

$PackageWebCoreEnd
