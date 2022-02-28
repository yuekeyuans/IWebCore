#pragma once

#include "orm/clause/IOrmCondition.h"

$PackageWebCoreBegin

class IOrmConditionImpl
{
public:
    IOrmConditionImpl();

    template<class T>
    QString condIn(const QString &field, const QList<T> &range,  IOrmCondition::Relation relation);

    template<class T>
    QString condBetween(const QString& field, const QPair<T, T>& range, IOrmCondition::Relation relation);

    QString condLike(const QString& field, const QString& value, IOrmCondition::Relation relation);
    QString condEndWith(const QString& field, const QString& value, IOrmCondition::Relation relation);
    QString condStartWith(const QString& field, const QString& value, IOrmCondition::Relation relation);
    QString condContain(const QString& field, const QString& value, IOrmCondition::Relation relation);
    QString condNotLike(const QString& field, const QString& value, IOrmCondition::Relation relation);

    QString condEqual(const QString& field, const QVariant& value, IOrmCondition::Relation relation);
    QString condNotEqual(const QString& field, const QVariant& value, IOrmCondition::Relation relation);
    QString condLessThan(const QString& field, const QVariant& value, IOrmCondition::Relation relation);
    QString condLessEqual(const QString& field, const QVariant& value, IOrmCondition::Relation relation);
    QString condGreatThan(const QString& field, const QVariant& value, IOrmCondition::Relation relation);
    QString condGreatEqual(const QString& field, const QVariant& value, IOrmCondition::Relation relation);

    QString condIsNull(const QString& field, IOrmCondition::Relation relation);
    QString condIsNotNull(const QString& field, IOrmCondition::Relation relation);


public:
    void appendWhereClause(const QString clause);
    void appendSubCondition(const IOrmCondition& condition);
    void appendHavingClause(const QString& clause);
    void appendGroupByClause(const QString& clause);
    void appendOrderByClause(const QString& clause);
    void setLimitClause(const QString& clause);
//    void append

    void bindParameters(ISqlQuery& query);
    void bindParameters(QSqlQuery& query);

    QString toSql(IOrmCondition::Type types);
    QString toWhereClause() const;
    QString toWhereClausePrivate() const;
    QString toOrderByClause() const;
    QString toGroupByClause() const;
    QString toHavingClause() const;
    QString toLimitClause() const;

    QMap<QString, QVariant> getParameters();

    void setNotClause();
    void setRelation(IOrmCondition::Relation relation);
    void setIsChildInstance(bool isChild = true);

    bool isValid();

private:
    QString getRelationTypeString(IOrmCondition::Relation type);
    QString getPlaceHolder(const QString& filedName);
    void setRelationType(IOrmCondition::Relation relation);

public:
    bool m_isChildInstance{false};  // 表示这个实例是一个子像
    bool m_isNotClause{false};
    IOrmCondition::Relation m_relation = IOrmCondition::Relation::And_Type;
    QMap<QString, QVariant> m_bindParameterMap;
    QStringList m_havingClauses;
    QMap<int, QString> m_whereClauses;
    QStringList m_orderByClauses;
    QStringList m_groupByClauses;
    QString m_limitClause;
    QMap<int, IOrmCondition> m_subConditions;
    QAtomicInteger<quint16> m_whereClauseIndex;

private:
    static QAtomicInteger<quint16> m_whereArgIndex; // quint16 is enough!
};

template<class T>
QString IOrmConditionImpl::condIn(const QString &field, const QList<T>& range, IOrmCondition::Relation relation)
{
    QStringList placeHolders;
    for(const auto& val : range){
        QString placeHolder = getPlaceHolder(field);
        placeHolders.append(placeHolder);
        m_bindParameterMap[placeHolder] = val;
    }

    QString sql = getRelationTypeString(relation).append('(')
            .append(field).append(" IN (").append(placeHolders.join(", ")).append(')').append(')');
    return sql;
}

template<class T>
QString IOrmConditionImpl::condBetween(const QString &field, const QPair<T, T>& range, IOrmCondition::Relation relation)
{
    QString ph1 = getPlaceHolder(field);
    QString ph2 = getPlaceHolder(field);

    m_bindParameterMap[ph1] = range.first;
    m_bindParameterMap[ph2] = range.second;

    QString sql = getRelationTypeString(relation).append('(')
            .append(field).append(" BETWEEN ").append(ph1).append(" AND ").append(ph2).append(')');
    return sql;
}

$PackageWebCoreEnd
