#pragma once

#include "base/IPreProcessorUtil.h"
#include "orm/pp/IOrmPreProcessor.h"

#define PP_AS_TABLE_COMMON(klassName) \
public: \
    static const IOrmTableInfo& tableInfo() { \
        static IOrmTableInfo m_tableInfo(staticMetaObject);  \
        return m_tableInfo; \
    }   \
    virtual const IOrmTableInfo& getTableInfo() const final{   \
        return tableInfo();  \
    }   \
private:

#define $AsTable_1(klassName) \
    $AsBean(klassName) \
    PP_AS_TABLE_COMMON(klassName) \
    Q_CLASSINFO("orm_entityName", #klassName) \
    Q_CLASSINFO("orm_entityType", PP_STRING(table))

#define $AsTable_2(klassName, tableName) \
    $AsBean(klassName) \
    PP_AS_TABLE_COMMON(klassName)   \
    Q_CLASSINFO("orm_entityName", #tableName) \
    Q_CLASSINFO("orm_entityType", PP_STRING(table))

#define $AsTable_(N) $AsTable_##N
#define $AsTable_EVAL(N) $AsTable_(N)
#define $AsTable(...) PP_EXPAND( $AsTable_EVAL(PP_EXPAND( PP_NARG(__VA_ARGS__) ))(__VA_ARGS__) )


#define $SqlType(name, type)  \
    Q_CLASSINFO(PP_STRING(sqlType__##name), #type)

#define $PrimaryKey(name) \
    $FieldIgnorable(name)   \
    Q_CLASSINFO(PP_STRING(primaryKey__##name), #name)

#define $NotNull(name)  \
    Q_CLASSINFO(PP_STRING(notNullKey__##name), #name)

#define $Unique(name) \
    Q_CLASSINFO(PP_STRING(uniqueKey__##name), #name)

#define $AutoGenerate_1(name) \
    $AutoGenerate_2(name, default)

#define $AutoGenerate_2(name, type) \
    Q_CLASSINFO(PP_STRING(autoIncrementKey__##name), #name) \
    Q_CLASSINFO(PP_STRING(autoIncrementType__##name), #type)

#define $AutoGenerate_(N) $AutoGenerate_##N
#define $AutoGenerate_EVAL(N) $AutoGenerate_(N)
#define $AutoGenerate(...) PP_EXPAND( $AutoGenerate_EVAL(PP_EXPAND( PP_NARG(__VA_ARGS__) ))(__VA_ARGS__) )

#define $TableField $Column
#define $TableFieldDeclare $ColumnDeclare
