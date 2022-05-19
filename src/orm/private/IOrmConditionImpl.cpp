#include "IOrmConditionImpl.h"
#include "orm/ISqlQuery.h"
#include "core/assertion/IAssertPreProcessor.h"

$PackageWebCoreBegin

static const char* const Sql_AndString= " AND ";
static const int         Sql_AndLength = 5;
static const char* const Sql_OrString = " OR ";
static const int         Sql_OrLength = 4;
static const char* const Sql_NotString = " NOT ";
//static const char* const Sql_AndNotString = "AND NOT ";
QAtomicInteger<quint16> IOrmConditionImpl::m_whereArgIndex = 0;

IOrmConditionImpl::IOrmConditionImpl()
{
}

QString IOrmConditionImpl::condLike(const QString &field, const QString &value, IOrmCondition::Relation relation)
{
    static const QString op = " LIKE ";
    QString placeHolder = getPlaceHolder(field);
    QString sql = getRelationTypeString(relation).append('(')
            .append(field).append(op).append(placeHolder).append(')');

    m_bindParameterMap[placeHolder] = value;
    return sql;
}

QString IOrmConditionImpl::condEndWith(const QString &field, const QString &value, IOrmCondition::Relation relation)
{
    static const QString op = " LIKE ";
    QString placeHolder = getPlaceHolder(field);
    QString sql = getRelationTypeString(relation).append('(')
            .append(field).append(op).append(placeHolder).append(')');

    m_bindParameterMap[placeHolder] = value + "%";
    return sql;
}

QString IOrmConditionImpl::condStartWith(const QString &field, const QString &value, IOrmCondition::Relation relation)
{
    static const QString op = " LIKE ";
    QString placeHolder = getPlaceHolder(field);
    QString sql = getRelationTypeString(relation).append('(')
            .append(field).append(op).append(placeHolder).append(')');

    m_bindParameterMap[placeHolder] = "%" + value;
    return sql;
}

QString IOrmConditionImpl::condContain(const QString &field, const QString &value, IOrmCondition::Relation relation)
{
    static const QString op = " LIKE ";
    QString placeHolder = getPlaceHolder(field);
    QString sql = getRelationTypeString(relation).append('(')
            .append(field).append(op).append(placeHolder).append(')');

    m_bindParameterMap[placeHolder] = "%" + value + "%";
    return sql;
}

QString IOrmConditionImpl::condNotLike(const QString &field, const QString &value, IOrmCondition::Relation relation)
{
    static const QString op = " NOT LIKE ";
    QString placeHolder = getPlaceHolder(field);
    QString sql = getRelationTypeString(relation).append('(')
            .append(field).append(op).append(placeHolder).append(')');

    m_bindParameterMap[placeHolder] = value;
    return sql;
}

QString IOrmConditionImpl::condEqual(const QString &field, const QVariant &value, IOrmCondition::Relation relation)
{
    static const char* op = " = ";

    QString sql;
    QString placeHolder = getPlaceHolder(field);
    sql.append(getRelationTypeString(relation)).append('(')
            .append(field).append(op).append(placeHolder).append(')');

    m_bindParameterMap[placeHolder] = value;
    return sql;
}

QString IOrmConditionImpl::condNotEqual(const QString &field, const QVariant &value, IOrmCondition::Relation relation)
{
    static const QString op = " <> ";
    QString placeHolder = getPlaceHolder(field);
    QString sql = getRelationTypeString(relation).append('(')
            .append(field).append(op).append(placeHolder).append(')');

    m_bindParameterMap[placeHolder] = value;
    return sql;
}

QString IOrmConditionImpl::condLessThan(const QString &field, const QVariant &value, IOrmCondition::Relation relation)
{
    static const QString op = " < ";
    QString placeHolder = getPlaceHolder(field);
    QString sql = getRelationTypeString(relation).append('(')
            .append(field).append(op).append(placeHolder).append(')');

    m_bindParameterMap.insert(placeHolder, value);
    return sql;
}

QString IOrmConditionImpl::condLessEqual(const QString &field, const QVariant &value, IOrmCondition::Relation relation)
{
    static const QString op = " <= ";
    QString placeHolder = getPlaceHolder(field);
    QString sql = getRelationTypeString(relation).append('(')
            .append(field).append(op).append(placeHolder).append(')');

    m_bindParameterMap[placeHolder] = value;
    return sql;
}

QString IOrmConditionImpl::condGreatThan(const QString &field, const QVariant &value, IOrmCondition::Relation relation)
{
    static const QString op = " > ";
    QString placeHolder = getPlaceHolder(field);
    QString sql = getRelationTypeString(relation).append('(')
            .append(field).append(op).append(placeHolder).append(')');

    m_bindParameterMap[placeHolder] = value;
    return sql;
}

QString IOrmConditionImpl::condGreatEqual(const QString &field, const QVariant &value, IOrmCondition::Relation relation)
{
    static const QString op = " >= ";
    QString placeHolder = getPlaceHolder(field);
    QString sql = getRelationTypeString(relation).append('(')
            .append(field).append(op).append(placeHolder).append(')');

    m_bindParameterMap[placeHolder] = value;
    return sql;
}

QString IOrmConditionImpl::condIsNull(const QString &field, IOrmCondition::Relation relation)
{
    static const QString op = " IS NULL";
    QString placeHolder = getPlaceHolder(field);
    QString sql = getRelationTypeString(relation).append('(')
            .append(field).append(op).append(')');
    return sql;
}

QString IOrmConditionImpl::condIsNotNull(const QString &field, IOrmCondition::Relation relation)
{
    static const QString op = " IS NOT NULL";
    QString placeHolder = getPlaceHolder(field);
    QString sql = getRelationTypeString(relation).append('(')
            .append(field).append(op).append(')');
    return sql;
}

void IOrmConditionImpl::appendWhereClause(const QString clause)
{
    m_whereClauses[m_whereClauseIndex.fetchAndAddRelaxed(1)] = clause;
}

void IOrmConditionImpl::appendSubCondition(const IOrmCondition &condition)
{
    m_subConditions[m_whereClauseIndex.fetchAndAddRelaxed(1)] = condition;
}

void IOrmConditionImpl::appendHavingClause(const QString &clause)
{
    m_havingClauses.append(clause);
}

void IOrmConditionImpl::appendGroupByClause(const QString &clause)
{
    m_groupByClauses.append(clause);
}

void IOrmConditionImpl::appendOrderByClause(const QString &clause)
{
    m_orderByClauses.append(clause);
}

void IOrmConditionImpl::setLimitClause(const QString &clause)
{
    m_limitClause = clause;
}

void IOrmConditionImpl::bindParameters(ISqlQuery &query)
{
    query.bindParameters(m_bindParameterMap);

    for(const auto& condition : m_subConditions){
        condition.bindParameters(query);
    }
}

void IOrmConditionImpl::bindParameters(QSqlQuery &query)
{
    auto keys = m_bindParameterMap.keys();
    for(const auto& key : keys){
        query.bindValue(key, m_bindParameterMap[key]);
    }

    for(const auto& condition : m_subConditions){
        condition.bindParameters(query);
    }
}

QString IOrmConditionImpl::toSql(IOrmCondition::Type types)
{
    QString sql;
    if((types & IOrmCondition::Where_Clause) != 0){
        auto where = toWhereClause();
        if(!where.isEmpty()){
            sql.append(where).append(' ');
        }
    }

    if(m_isChildInstance){
        return sql.trimmed();   // child 实例不处理 where 意外的任何东西
    }

    if((types & IOrmCondition::GroupBy_Clause)){
        auto groupBy = toGroupByClause();
        if(!groupBy.isEmpty()){
            sql.append(groupBy).append(' ');
        }
    }

    if((types & IOrmCondition::OrderBy_Clause)){
        auto orderBy = toOrderByClause();
        if(!orderBy.isEmpty()){
            sql.append(orderBy).append(' ');
        }
    }

    if((types & IOrmCondition::Limit_Clause) != 0){
        auto limit = toLimitClause();
        if(!limit.isEmpty()){
            sql.append(limit).append(' ');
        }
    }

    return sql.trimmed();
}

QString IOrmConditionImpl::toWhereClause() const
{
    auto where = toWhereClausePrivate();
    if(where.isEmpty()){
        return QString();
    }

    if(where.startsWith(Sql_AndString)){
        return QString("WHERE ").append(where.midRef(Sql_AndLength));
    }

    if(where.startsWith(Sql_OrString)){
        IAssertDetail detail;
        detail["origin sql"] = where;
        $AssertWarning(where_sql_start_with_OR, detail);

        return QString("WHERE ").append(where.midRef(Sql_OrLength));
    }

    return QString("WHERE ").append(where);
}

/**
 * @brief IOrmCondition::toWhereClausePrivate
 * @return
 * 这里返回的值是 所有的子项 join 后，加上 and / or /and not /or not.
 * 所以其返回值必定是以 and / or 开头
 * 但是 子项的头一项 以 Or 开头又是一个异常项目。 因为sql 中间没有 以 where or 开头的，
 * 同样这件事情视为warn 而不是 fatal.
 */
QString IOrmConditionImpl::toWhereClausePrivate() const
{
    QStringList clauseList;
    int count = m_whereClauses.size() + m_subConditions.size();
    static const int andLength = 5;

    for(int i=0; i<count; ++i){
        if(m_whereClauses.contains(i)){
            clauseList.append(m_whereClauses[i]);
            continue;
        }

        if(m_subConditions.contains(i)){
            auto subWhere = m_subConditions[i].impl->toWhereClausePrivate();
            if(subWhere.isEmpty()){
                continue;   // tollerant, 可以为空
            }
            clauseList.append(subWhere);
        }
    }

    QString clause = clauseList.join("");

    if(clause.trimmed().isEmpty()){
        return QString();
    }

    // 处理 and 开头的内容
    if(clause.startsWith(Sql_AndString)){
        if(m_relation == IOrmCondition::And_Type){
            if(m_isNotClause){
                return QString(" AND NOT (").append(clause.midRef(andLength)).append(')');
            }
            return QString(" AND (").append(clause.midRef(andLength)).append(')');
        }else if(m_relation == IOrmCondition::Or_Type){
            if(m_isNotClause){
                return QString(" OR NOT (").append(clause.midRef(andLength)).append(')');
            }
            return QString(" OR (").append(clause.midRef(andLength)).append(')');
        }
    }

    // 处理 or 开头的内容
    if(clause.startsWith(Sql_OrString)){
        IAssertDetail detail;
        detail["origin Sql"] = clause;
        $AssertWarning(where_sql_start_with_OR, detail)
        return clause;
    }

    // 处理 NOT 开头的内容
    if(clause.startsWith(Sql_NotString)){
        IAssertDetail detail;
        detail["origin Sql"] = clause;
        $AssertWarning(where_sql_start_with_NOT, detail)
    }
    return clause;
}

QString IOrmConditionImpl::toOrderByClause() const
{
    QString sql;
    if(!m_orderByClauses.isEmpty()){
        sql.append("ORDER BY ").append(m_orderByClauses.join(", "));
    }
    return sql;
}

QString IOrmConditionImpl::toGroupByClause() const
{
    QString sql;
    if(!m_groupByClauses.isEmpty()){
         sql.append("GROUP BY ").append(m_groupByClauses.join(" ,"));
    }
    return sql;
}

QString IOrmConditionImpl::toHavingClause() const
{
    QString sql;
    if(!m_havingClauses.isEmpty()){
        sql.append("HAVING ").append(m_havingClauses.join(" AND "));
    }
    return sql;
}

QString IOrmConditionImpl::toLimitClause() const
{
    return m_limitClause;
}

QMap<QString, QVariant> IOrmConditionImpl::getParameters()
{
    QMap<QString, QVariant> map;
    map = m_bindParameterMap;
    for(auto const& condition : m_subConditions){
        auto conMap = condition.getParameters();
        for(auto key : conMap.keys()){
            map[key] = conMap[key];
        }
    }
    return map;
}

void IOrmConditionImpl::setNotClause()
{
    m_isNotClause = !m_isNotClause;
}

void IOrmConditionImpl::setRelation(IOrmCondition::Relation relation)
{
    this->m_relation = relation;
}

void IOrmConditionImpl::setIsChildInstance(bool isChild)
{
    this->m_isChildInstance = isChild;
}

bool IOrmConditionImpl::isValid()
{
    if(m_whereClauses.isEmpty()
            && m_orderByClauses.isEmpty()
            && m_subConditions.isEmpty()){
        return false;
    }
    return true;
}

QString IOrmConditionImpl::getRelationTypeString(IOrmCondition::Relation type)
{
    switch (type) {
    case IOrmCondition::Relation::Or_Type:
        return QString(" OR ");
    case IOrmCondition::Relation::And_Type:
        return QString(" AND ");
    }
    return QString();
}

QString IOrmConditionImpl::getPlaceHolder(const QString &field)
{
    static QString sql = ":";
    sql.resize(1);

    auto number = m_whereArgIndex.fetchAndAddRelaxed(1);

    return sql.append(field).append('_').append(QString::number(number));
}

void IOrmConditionImpl::setRelationType(IOrmCondition::Relation relation)
{
    this->m_relation = relation;
}

$PackageWebCoreEnd
