#pragma once

#include "IHeaderUtil.h"

$PackageWebCoreBegin

/*! @namespace IConstantUtil
 * @brief list some often used constants.
 *
 **/
namespace IConstantUtil
{
    // debugMode;
#ifdef QT_DEBUG
    static constexpr bool DebugMode = true;
    static constexpr bool ReleaseMode = false;
#else
    static constexpr bool DebugMode = true;
    static constexpr bool ReleaseMode = false;
#endif

    //! official Date format
    static const QString DateFormat = "yyyy-MM-dd";
    static const QString TimeFormat = "hh:mm:ss.zzz";
    static const QString DateTimeFormat = "yyyy-MM-dd hh:mm:ss.zzz";

    ////////// config
    static const char* const Config_Prefix = "iwebConfigWire__";

    static const char* const StatusControllerPrefix = "iwebStatusFun$";

    //! char[] of new line.
    static const char* const NewLine = "\r\n";

    static const char* const InheritedMethod = "inherited method";
    static const char* const UnImplimentedMethod = "unimplimented method, this will be implimented latter";

    ////////// sql
    static const char* const Sql_PrimayKeyClause = "primaryKey__";
    static const char* const Sql_UniqueKeyClause = "uniqueKey__";
    static const char* const Sql_NotNulKeyClause = "notNullKey__";
    static const char* const Sql_AutoGenerateKeyClause = "autoIncrementKey__";
    static const char* const Sql_AutoGenerateTypeClause = "autoIncrementType__";
    static const char* const Sql_SqlTypeKeyClause = "sqlType__";

    static const QMetaType::Type PrimaryKeyTypes[4] = {QMetaType::Int, QMetaType::Long, QMetaType::LongLong, QMetaType::QString};

    // length;
    static constexpr int Request_Url_Max_Length = (2048 + 35);  // 2083
    static constexpr int Request_Header_Max_Length = (1024 * 8); // 8K
    static constexpr int Request_Body_Max_Length   = (1024 * 1024 * 4);  // 4M
};

$PackageWebCoreEnd
