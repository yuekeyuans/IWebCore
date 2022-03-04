#pragma once

#include "orm/pp/IOrmPreProcessor.h"

#define PP_AS_VIEW_COMMON(klassName)    \
public: \
    static const IOrmViewInfo& entityInfo() { \
        static IOrmViewInfo m_viewInfo(staticMetaObject);  \
        return m_viewInfo; \
    }   \
    virtual const IOrmViewInfo* getOrmEntityInfo() const final{   \
        return &entityInfo();  \
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
