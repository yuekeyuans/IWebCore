#include "UserBean.h"

UserBean::UserBean()
{
    do{
        auto info = getTableInfo();
        auto pkTypeId = info.getFieldTypeId(info.primaryKey);
        if(pkTypeId == QMetaType::Int){
            setFieldValue(info.primaryKey, PRIMARY_KEY_INTEGER_NULL);
        }else if(pkTypeId == QMetaType::QString){
            setFieldValue(info.primaryKey, PRIMARY_KEY_STRING_NULL);
        }
    }while(0);
}
