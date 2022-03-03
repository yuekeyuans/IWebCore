#pragma once

#include "orm/pp/IOrmPreProcessor.h"

#define PP_AS_VIEW_COMMON(klassName)

#define ABCD    \
public: \
    static const IOrmTableInfo& tableInfo() { \
        static IOrmTableInfo m_tableInfo(staticMetaObject);  \
        return m_tableInfo; \
    }   \
    virtual const IOrmTableInfo& getTableInfo() const final{   \
        return tableInfo();  \
    }   \
private:

#define $AsView_1(klassName) \
    $AsBean(klassName) \
    PP_AS_VIEW_COMMON(klassName) \
    Q_CLASSINFO("orm_entityName", #klassName) \
    Q_CLASSINFO("orm_entityType", PP_STRING(view))

#define $AsView_2(klassName, viewName) \
    $AsBean(klassName) \
    PP_AS_VIEW_COMMON(klassName)   \
    Q_CLASSINFO("orm_entityName", #viewName) \
    Q_CLASSINFO("orm_entityType", PP_STRING(view))

#define $AsView_(N) $AsView_##N
#define $AsView_EVAL(N) $AsView_(N)
#define $AsView(...) PP_EXPAND( $AsView_EVAL(PP_EXPAND( PP_NARG(__VA_ARGS__) ))(__VA_ARGS__) )

#define $ViewField $Column
#define $ViewFieldDeclare $ColumnDeclare
