#pragma once

#include "core/util/IHeaderUtil.h"

$PackageWebCoreBegin

class ISqlQuery : public QSqlQuery
{
public:
    using QueryLog = void(*)(const QSqlQuery& query);

    using QSqlQuery::QSqlQuery;

    ISqlQuery& operator=(const ISqlQuery& other);

    ~ISqlQuery();

    bool exec(const QString& sql);
    bool exec();

    void binParameter(const QString& key, const QVariant& value);
    void bindParameters(const QMap<QString, QVariant>& map);

private:
    void bindExecParameters();

    static bool isEnableSqlPrint();

private:
    QMap<QString, QVariant> m_parameters;
};

$PackageWebCoreEnd
