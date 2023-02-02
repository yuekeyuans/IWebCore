#include "core/base/IHeaderUtil.h"

#include <stdio.h>
#include <stdlib.h>
#include "IOrmCondition.h"
#include "core/base/IConstantUtil.h"
#include "orm/ISqlQuery.h"
#include "orm/dialect/IOrmDialectWare.h"
#include "orm/private/IOrmConditionImpl.h"

$PackageWebCoreBegin

IOrmCondition::IOrmCondition() : impl(std::make_shared<IOrmConditionImpl>())
{
}

IOrmCondition &IOrmCondition::where(const QString &clause)
{
    impl->appendWhereClause(clause);
    return *this;
}

IOrmCondition &IOrmCondition::whereBetween(const QString &field, QVariant lowerBound, QVariant upperBound, IOrmCondition::Relation relation)
{
    auto sql = impl->condBetween(field, QPair<QVariant, QVariant>{lowerBound, upperBound}, relation);
    impl->appendWhereClause(sql);
    return *this;
}

IOrmCondition &IOrmCondition::whereLike(const QString &field, const QString &value, IOrmCondition::Relation relation)
{
    auto sql = impl->condLike(field, value, relation);
    impl->appendWhereClause(sql);
    return *this;
}

IOrmCondition &IOrmCondition::whereEndWith(const QString &field, const QString &value, IOrmCondition::Relation relation)
{
    auto sql = impl->condEndWith(field, value, relation);
    impl->appendWhereClause(sql);
    return *this;
}

IOrmCondition &IOrmCondition::whereStartWith(const QString &field, const QString &value, IOrmCondition::Relation relation)
{
    auto sql = impl->condStartWith(field, value, relation);
    impl->appendWhereClause(sql);
    return *this;
}

IOrmCondition &IOrmCondition::whereContain(const QString &field, const QString &value, IOrmCondition::Relation relation)
{
    auto sql = impl->condContain(field, value, relation);
    impl->appendWhereClause(sql);
    return *this;
}

IOrmCondition &IOrmCondition::whereNotLike(const QString &field, const QString &value, IOrmCondition::Relation relation)
{
    auto sql = impl->condNotLike(field, value, relation);
    impl->appendWhereClause(sql);
    return *this;
}

IOrmCondition &IOrmCondition::whereIsNull(const QString &field, IOrmCondition::Relation relation)
{
    QString sql = impl->condIsNull(field, relation);
    impl->appendWhereClause(sql);
    return *this;
}

IOrmCondition &IOrmCondition::whereIsNotNull(const QString &field, IOrmCondition::Relation relation)
{
    QString sql = impl->condIsNotNull(field, relation);
    impl->appendWhereClause(sql);
    return *this;
}

IOrmCondition &IOrmCondition::whereEqual(const QString &field, const QVariant &value, IOrmCondition::Relation relation)
{
    QString sql = impl->condEqual(field, value, relation);
    impl->appendWhereClause(sql);
    return *this;
}

IOrmCondition &IOrmCondition::whereNotEqual(const QString &field, const QVariant &value, IOrmCondition::Relation relation)
{
    QString sql = impl->condEqual(field, value, relation);
    impl->appendWhereClause(sql);
    return *this;
}

IOrmCondition &IOrmCondition::whereLessThan(const QString &field, const QVariant &value, IOrmCondition::Relation relation)
{
    QString sql = impl->condLessThan(field, value, relation);
    impl->appendWhereClause(sql);
    return *this;
}

IOrmCondition &IOrmCondition::whereLessEqual(const QString &field, const QVariant &value, IOrmCondition::Relation relation)
{
    QString sql = impl->condLessEqual(field, value, relation);
    impl->appendWhereClause(sql);
    return *this;
}

IOrmCondition &IOrmCondition::whereGreatThan(const QString &field, const QVariant &value, IOrmCondition::Relation relation)
{
    QString sql = impl->condGreatThan(field, value, relation);
    impl->appendWhereClause(sql);
    return *this;
}

IOrmCondition &IOrmCondition::whereGreatEqual(const QString &field, const QVariant &value, IOrmCondition::Relation relation)
{
    QString sql = impl->condGreatEqual(field, value, relation);
    impl->appendWhereClause(sql);
    return *this;
}

IOrmCondition &IOrmCondition::whereTrue()
{
    static const QString sql = "(1 = 1)";
    impl->appendWhereClause(sql);
    return *this;
}

IOrmCondition &IOrmCondition::whereFalse()
{
    static const QString sql = "(1 <> 1)";
    impl->appendWhereClause(sql);
    return *this;
}

IOrmCondition &IOrmCondition::having(const QString &clause)
{
    impl->appendHavingClause(clause);
    return *this;
}

IOrmCondition &IOrmCondition::havingBetween(const QString &field, const QVariant &lowerBound, const QVariant &upperBound, IOrmCondition::Relation relation)
{
    auto sql = impl->condBetween(field, QPair<QVariant, QVariant>{lowerBound, upperBound}, relation);
    impl->appendHavingClause(sql);
    return *this;
}

IOrmCondition &IOrmCondition::havingEqual(const QString &field, const QVariant &value, IOrmCondition::Relation relation)
{
    auto sql = impl->condEqual(field, value, relation);
    impl->appendHavingClause(sql);
    return *this;
}

IOrmCondition &IOrmCondition::havingNotEqual(const QString &field, const QVariant &value, IOrmCondition::Relation relation)
{
    auto sql = impl->condNotEqual(field, value, relation);
    impl->appendHavingClause(sql);
    return *this;
}

IOrmCondition &IOrmCondition::havingLessThan(const QString &field, const QVariant &value, IOrmCondition::Relation relation)
{
    auto sql = impl->condLessThan(field, value, relation);
    impl->appendHavingClause(sql);
    return *this;
}

IOrmCondition &IOrmCondition::havingLessEqual(const QString &field, const QVariant &value, IOrmCondition::Relation relation)
{
    auto sql = impl->condLessEqual(field, value, relation);
    impl->appendHavingClause(sql);
    return *this;
}

IOrmCondition &IOrmCondition::havingGreatThan(const QString &field, const QVariant &value, IOrmCondition::Relation relation)
{
    auto sql = impl->condGreatThan(field, value, relation);
    impl->appendHavingClause(sql);
    return *this;
}

IOrmCondition &IOrmCondition::havingGreatEqual(const QString &field, const QVariant &value, IOrmCondition::Relation relation)
{
    auto sql = impl->condGreatEqual(field, value, relation);
    impl->appendHavingClause(sql);
    return *this;
}

IOrmCondition &IOrmCondition::conditionAnd(IOrmCondition condition)
{
    condition.impl->setRelation(And_Type);
    condition.impl->setIsChildInstance(true);
    impl->appendSubCondition(condition);
    return *this;
}

IOrmCondition &IOrmCondition::conditionOr(IOrmCondition condition)
{
    condition.impl->setRelation(Or_Type);
    condition.impl->setIsChildInstance(true);
    impl->appendSubCondition(condition);
    return *this;
}

IOrmCondition &IOrmCondition::conditionAndNot(IOrmCondition condition)
{
    condition.impl->setRelation(And_Type);
    condition.impl->setNotClause();
    condition.impl->setIsChildInstance(true);
    impl->appendSubCondition(condition);
    return *this;
}

IOrmCondition &IOrmCondition::conditionOrNot(IOrmCondition condition)
{
    condition.impl->setRelation(Or_Type);
    condition.impl->setNotClause();
    condition.impl->setIsChildInstance(true);
    impl->appendSubCondition(condition);
    return *this;
}

IOrmCondition &IOrmCondition::conditionNot(IOrmCondition &condition)
{
    condition.impl->setNotClause();
    return condition;
}

IOrmCondition &IOrmCondition::orderByAsc(const QString &field)
{
    QString sql;
    sql.append(field).append(" ASC");
    impl->appendOrderByClause(sql);
    return *this;
}

IOrmCondition &IOrmCondition::orderByDesc(const QString &field)
{
    QString sql;
    sql.append(field).append(" DESC");
    impl->appendOrderByClause(sql);
    return *this;
}

IOrmCondition &IOrmCondition::groupBy(const QString &field)
{
    impl->appendGroupByClause(field);
    return *this;
}

IOrmCondition &IOrmCondition::limit(IOrmDialectWare *dialect, quint64 count)
{
    impl->setLimitClause(dialect->getLimitString(count));
    return *this;
}

IOrmCondition &IOrmCondition::limit(IOrmDialectWare *dialect, quint64 start, quint64 count)
{
    impl->setLimitClause(dialect->getLimitString(start, count));
    return *this;
}

QString IOrmCondition::toSql(IOrmCondition::Type types) const
{
    return impl->toSql(types);
}

QString IOrmCondition::toWhereClause() const
{
    return impl->toWhereClause();
}

QString IOrmCondition::toOrderByClause() const
{
    return impl->toOrderByClause();
}

QString IOrmCondition::toGroupByClause() const
{
    return impl->toGroupByClause();
}

QString IOrmCondition::toLimitClause() const
{
    return impl->toLimitClause();
}

QString IOrmCondition::toHavingClause() const
{
    return impl->toHavingClause();
}

// NOTE: this is only for test case use.
QMap<QString, QVariant> IOrmCondition::getParameters() const
{
    return impl->getParameters();
}

void IOrmCondition::bindParameters(ISqlQuery &query) const
{
    impl->bindParameters(query);
}

void IOrmCondition::bindParameters(QSqlQuery &query) const
{
    impl->bindParameters(query);
}

bool IOrmCondition::isValid() const
{
    return impl->isValid();
}

void IOrmConditionHelper::whereIn(std::shared_ptr<IOrmConditionImpl> impl, const QString &field, const QList<qint8> &range, IOrmCondition::Relation relation)
{
    auto sql = impl->condIn(field, range, relation);
    impl->appendWhereClause(sql);
}

void IOrmConditionHelper::whereIn(std::shared_ptr<IOrmConditionImpl> impl, const QString &field, const QList<quint8> &range, IOrmCondition::Relation relation)
{
    auto sql = impl->condIn(field, range, relation);
    impl->appendWhereClause(sql);
}

void IOrmConditionHelper::whereIn(std::shared_ptr<IOrmConditionImpl> impl, const QString &field, const QList<qint16> &range, IOrmCondition::Relation relation)
{
    auto sql = impl->condIn(field, range, relation);
    impl->appendWhereClause(sql);
}

void IOrmConditionHelper::whereIn(std::shared_ptr<IOrmConditionImpl> impl, const QString &field, const QList<quint16> &range, IOrmCondition::Relation relation)
{
    auto sql = impl->condIn(field, range, relation);
    impl->appendWhereClause(sql);
}

void IOrmConditionHelper::whereIn(std::shared_ptr<IOrmConditionImpl> impl, const QString &field, const QList<qint32> &range, IOrmCondition::Relation relation)
{
    auto sql = impl->condIn(field, range, relation);
    impl->appendWhereClause(sql);
}

void IOrmConditionHelper::whereIn(std::shared_ptr<IOrmConditionImpl> impl, const QString &field, const QList<quint32> &range, IOrmCondition::Relation relation)
{
    auto sql = impl->condIn(field, range, relation);
    impl->appendWhereClause(sql);
}

void IOrmConditionHelper::whereIn(std::shared_ptr<IOrmConditionImpl> impl, const QString &field, const QList<quint64> &range, IOrmCondition::Relation relation)
{
    auto sql = impl->condIn(field, range, relation);
    impl->appendWhereClause(sql);
}

void IOrmConditionHelper::whereIn(std::shared_ptr<IOrmConditionImpl> impl, const QString &field, const QList<qint64> &range, IOrmCondition::Relation relation)
{
    auto sql = impl->condIn(field, range, relation);
    impl->appendWhereClause(sql);
}

void IOrmConditionHelper::whereIn(std::shared_ptr<IOrmConditionImpl> impl, const QString &field, const QList<float> &range, IOrmCondition::Relation relation)
{
    auto sql = impl->condIn(field, range, relation);
    impl->appendWhereClause(sql);
}

void IOrmConditionHelper::whereIn(std::shared_ptr<IOrmConditionImpl> impl, const QString &field, const QList<double> &range, IOrmCondition::Relation relation)
{
    auto sql = impl->condIn(field, range, relation);
    impl->appendWhereClause(sql);
}

void IOrmConditionHelper::whereIn(std::shared_ptr<IOrmConditionImpl> impl, const QString &field, const QList<QString> &range, IOrmCondition::Relation relation)
{
    auto sql = impl->condIn(field, range, relation);
    impl->appendWhereClause(sql);
}

void IOrmConditionHelper::whereIn(std::shared_ptr<IOrmConditionImpl> impl, const QString &field, const QList<QVariant> &range, IOrmCondition::Relation relation)
{
    auto sql = impl->condIn(field, range, relation);
    impl->appendWhereClause(sql);
}

void IOrmConditionHelper::whereIn(std::shared_ptr<IOrmConditionImpl> impl, const QString &field, const QList<QDate> &range, IOrmCondition::Relation relation)
{
    auto sql = impl->condIn(field, range, relation);
    impl->appendWhereClause(sql);
}

void IOrmConditionHelper::whereIn(std::shared_ptr<IOrmConditionImpl> impl, const QString &field, const QList<QTime> &range, IOrmCondition::Relation relation)
{
    auto sql = impl->condIn(field, range, relation);
    impl->appendWhereClause(sql);
}

void IOrmConditionHelper::whereIn(std::shared_ptr<IOrmConditionImpl> impl, const QString &field, const QList<QDateTime> &range, IOrmCondition::Relation relation)
{
    auto sql = impl->condIn(field, range, relation);
    impl->appendWhereClause(sql);
}

void IOrmConditionHelper::whereIn(std::shared_ptr<IOrmConditionImpl> impl, const QString &field, const QStringList &range, IOrmCondition::Relation relation)
{
    auto sql = impl->condIn(field, range, relation);
    impl->appendWhereClause(sql);
}



void IOrmConditionHelper::whereBetween(std::shared_ptr<IOrmConditionImpl> impl, const QString &field, const QPair<qint8, qint8>& range, IOrmCondition::Relation relation)
{
    auto sql = impl->condBetween(field, range, relation);
    impl->appendWhereClause(sql);
}

void IOrmConditionHelper::whereBetween(std::shared_ptr<IOrmConditionImpl> impl, const QString &field, const QPair<quint8, quint8>& range, IOrmCondition::Relation relation)
{
    auto sql = impl->condBetween(field, range, relation);
    impl->appendWhereClause(sql);
}

void IOrmConditionHelper::whereBetween(std::shared_ptr<IOrmConditionImpl> impl, const QString &field, const QPair<qint16, qint16>& range, IOrmCondition::Relation relation)
{
    auto sql = impl->condBetween(field, range, relation);
    impl->appendWhereClause(sql);
}

void IOrmConditionHelper::whereBetween(std::shared_ptr<IOrmConditionImpl> impl, const QString &field, const QPair<quint16, quint16>& range, IOrmCondition::Relation relation)
{
    auto sql = impl->condBetween(field, range, relation);
    impl->appendWhereClause(sql);
}

void IOrmConditionHelper::whereBetween(std::shared_ptr<IOrmConditionImpl> impl, const QString &field, const QPair<qint32, qint32>& range, IOrmCondition::Relation relation)
{
    auto sql = impl->condBetween(field, range, relation);
    impl->appendWhereClause(sql);
}

void IOrmConditionHelper::whereBetween(std::shared_ptr<IOrmConditionImpl> impl, const QString &field, const QPair<quint32, quint32>& range, IOrmCondition::Relation relation)
{
    auto sql = impl->condBetween(field, range, relation);
    impl->appendWhereClause(sql);
}

void IOrmConditionHelper::whereBetween(std::shared_ptr<IOrmConditionImpl> impl, const QString &field, const QPair<qint64, qint64>& range, IOrmCondition::Relation relation)
{
    auto sql = impl->condBetween(field, range, relation);
    impl->appendWhereClause(sql);
}

void IOrmConditionHelper::whereBetween(std::shared_ptr<IOrmConditionImpl> impl, const QString &field, const QPair<quint64, quint64>& range, IOrmCondition::Relation relation)
{
    auto sql = impl->condBetween(field, range, relation);
    impl->appendWhereClause(sql);
}

void IOrmConditionHelper::whereBetween(std::shared_ptr<IOrmConditionImpl> impl, const QString &field, const QPair<float, float>& range, IOrmCondition::Relation relation)
{
    auto sql = impl->condBetween(field, range, relation);
    impl->appendWhereClause(sql);
}

void IOrmConditionHelper::whereBetween(std::shared_ptr<IOrmConditionImpl> impl, const QString &field, const QPair<double, double>& range, IOrmCondition::Relation relation)
{
    auto sql = impl->condBetween(field, range, relation);
    impl->appendWhereClause(sql);
}

void IOrmConditionHelper::whereBetween(std::shared_ptr<IOrmConditionImpl> impl, const QString &field, const QPair<QString, QString>& range, IOrmCondition::Relation relation)
{

    auto sql = impl->condBetween(field, range, relation);
    impl->appendWhereClause(sql);
}

void IOrmConditionHelper::whereBetween(std::shared_ptr<IOrmConditionImpl> impl, const QString &field, const QPair<QVariant, QVariant>& range, IOrmCondition::Relation relation)
{

    auto sql = impl->condBetween(field, range, relation);
    impl->appendWhereClause(sql);
}

void IOrmConditionHelper::whereBetween(std::shared_ptr<IOrmConditionImpl> impl, const QString &field, const QPair<QDate, QDate>& range, IOrmCondition::Relation relation)
{

    auto sql = impl->condBetween(field, range, relation);
    impl->appendWhereClause(sql);
}

void IOrmConditionHelper::whereBetween(std::shared_ptr<IOrmConditionImpl> impl, const QString &field, const QPair<QTime, QTime>& range, IOrmCondition::Relation relation)
{
    auto sql = impl->condBetween(field, range, relation);
    impl->appendWhereClause(sql);
}

void IOrmConditionHelper::whereBetween(std::shared_ptr<IOrmConditionImpl> impl, const QString &field, const QPair<QDateTime, QDateTime>& range, IOrmCondition::Relation relation)
{
    auto sql = impl->condBetween(field, range, relation);
    impl->appendWhereClause(sql);
}

void IOrmConditionHelper::havingIn(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QList<qint8> &range, IOrmCondition::Relation relation)
{
    auto sql = impl->condIn(field, range, relation);
    impl->appendHavingClause(sql);
}

void IOrmConditionHelper::havingIn(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QList<quint8> &range, IOrmCondition::Relation relation)
{
    auto sql = impl->condIn(field, range, relation);
    impl->appendHavingClause(sql);
}

void IOrmConditionHelper::havingIn(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QList<qint16> &range, IOrmCondition::Relation relation)
{
    auto sql = impl->condIn(field, range, relation);
    impl->appendHavingClause(sql);
}

void IOrmConditionHelper::havingIn(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QList<quint16> &range, IOrmCondition::Relation relation)
{
    auto sql = impl->condIn(field, range, relation);
    impl->appendHavingClause(sql);
}

void IOrmConditionHelper::havingIn(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QList<qint32> &range, IOrmCondition::Relation relation)
{
    auto sql = impl->condIn(field, range, relation);
    impl->appendHavingClause(sql);
}

void IOrmConditionHelper::havingIn(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QList<quint32> &range, IOrmCondition::Relation relation)
{
    auto sql = impl->condIn(field, range, relation);
    impl->appendHavingClause(sql);
}

void IOrmConditionHelper::havingIn(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QList<quint64> &range, IOrmCondition::Relation relation)
{
    auto sql = impl->condIn(field, range, relation);
    impl->appendHavingClause(sql);
}

void IOrmConditionHelper::havingIn(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QList<qint64> &range, IOrmCondition::Relation relation)
{
    auto sql = impl->condIn(field, range, relation);
    impl->appendHavingClause(sql);
}

void IOrmConditionHelper::havingIn(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QList<float> &range, IOrmCondition::Relation relation)
{
    auto sql = impl->condIn(field, range, relation);
    impl->appendHavingClause(sql);
}

void IOrmConditionHelper::havingIn(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QList<double> &range, IOrmCondition::Relation relation)
{
    auto sql = impl->condIn(field, range, relation);
    impl->appendHavingClause(sql);
}

void IOrmConditionHelper::havingIn(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QList<QString> &range, IOrmCondition::Relation relation)
{
    auto sql = impl->condIn(field, range, relation);
    impl->appendHavingClause(sql);
}

void IOrmConditionHelper::havingIn(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QList<QVariant> &range, IOrmCondition::Relation relation)
{
    auto sql = impl->condIn(field, range, relation);
    impl->appendHavingClause(sql);
}

void IOrmConditionHelper::havingIn(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QList<QDate> &range, IOrmCondition::Relation relation)
{
    auto sql = impl->condIn(field, range, relation);
    impl->appendHavingClause(sql);
}

void IOrmConditionHelper::havingIn(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QList<QTime> &range, IOrmCondition::Relation relation)
{
    auto sql = impl->condIn(field, range, relation);
    impl->appendHavingClause(sql);
}

void IOrmConditionHelper::havingIn(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QList<QDateTime> &range, IOrmCondition::Relation relation)
{
    auto sql = impl->condIn(field, range, relation);
    impl->appendHavingClause(sql);
}

void IOrmConditionHelper::havingIn(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QStringList &range, IOrmCondition::Relation relation)
{
    auto sql = impl->condIn(field, range, relation);
    impl->appendHavingClause(sql);
}


void IOrmConditionHelper::havingBetween(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QPair<qint8, qint8> &range, IOrmCondition::Relation relation)
{
    auto sql = impl->condBetween(field, range, relation);
    impl->appendHavingClause(sql);
}

void IOrmConditionHelper::havingBetween(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QPair<quint8, quint8> &range, IOrmCondition::Relation relation)
{
    auto sql = impl->condBetween(field, range, relation);
    impl->appendHavingClause(sql);
}

void IOrmConditionHelper::havingBetween(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QPair<qint16, qint16> &range, IOrmCondition::Relation relation)
{
    auto sql = impl->condBetween(field, range, relation);
    impl->appendHavingClause(sql);
}

void IOrmConditionHelper::havingBetween(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QPair<quint16, quint16> &range, IOrmCondition::Relation relation)
{
    auto sql = impl->condBetween(field, range, relation);
    impl->appendHavingClause(sql);
}

void IOrmConditionHelper::havingBetween(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QPair<qint32, qint32> &range, IOrmCondition::Relation relation)
{
    auto sql = impl->condBetween(field, range, relation);
    impl->appendHavingClause(sql);
}

void IOrmConditionHelper::havingBetween(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QPair<quint32, quint32> &range, IOrmCondition::Relation relation)
{
    auto sql = impl->condBetween(field, range, relation);
    impl->appendHavingClause(sql);
}

void IOrmConditionHelper::havingBetween(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QPair<qint64, qint64> &range, IOrmCondition::Relation relation)
{
    auto sql = impl->condBetween(field, range, relation);
    impl->appendHavingClause(sql);
}

void IOrmConditionHelper::havingBetween(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QPair<quint64, quint64> &range, IOrmCondition::Relation relation)
{
    auto sql = impl->condBetween(field, range, relation);
    impl->appendHavingClause(sql);
}

void IOrmConditionHelper::havingBetween(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QPair<float, float> &range, IOrmCondition::Relation relation)
{
    auto sql = impl->condBetween(field, range, relation);
    impl->appendHavingClause(sql);
}

void IOrmConditionHelper::havingBetween(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QPair<double, double> &range, IOrmCondition::Relation relation)
{
    auto sql = impl->condBetween(field, range, relation);
    impl->appendHavingClause(sql);
}

void IOrmConditionHelper::havingBetween(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QPair<QString, QString> &range, IOrmCondition::Relation relation)
{
    auto sql = impl->condBetween(field, range, relation);
    impl->appendHavingClause(sql);
}

void IOrmConditionHelper::havingBetween(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QPair<QVariant, QVariant> &range, IOrmCondition::Relation relation)
{
    auto sql = impl->condBetween(field, range, relation);
    impl->appendHavingClause(sql);
}

void IOrmConditionHelper::havingBetween(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QPair<QDate, QDate> &range, IOrmCondition::Relation relation)
{
    auto sql = impl->condBetween(field, range, relation);
    impl->appendHavingClause(sql);
}

void IOrmConditionHelper::havingBetween(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QPair<QTime, QTime> &range, IOrmCondition::Relation relation)
{
    auto sql = impl->condBetween(field, range, relation);
    impl->appendHavingClause(sql);
}

void IOrmConditionHelper::havingBetween(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QPair<QDateTime, QDateTime> &range, IOrmCondition::Relation relation)
{
    auto sql = impl->condBetween(field, range, relation);
    impl->appendHavingClause(sql);
}



$PackageWebCoreEnd
