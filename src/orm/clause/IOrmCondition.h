#pragma once

#include "base/IHeaderUtil.h"
#include <cstdint>

$PackageWebCoreBegin

class ISqlQuery;
class IOrmDialectWare;
class IOrmConditionImpl;

class IOrmCondition
{
public:
    enum Relation : uint8_t{
        And_Type,
        Or_Type,
    };

    enum Type : uint8_t{
        Where_Clause    = 1 << 0,
        OrderBy_Clause  = 1 << 1,
        GroupBy_Clause  = 1 << 2,
        Having_Clause   = 1 << 3,
        Limit_Clause    = 1 << 4,
        Default         = Where_Clause | OrderBy_Clause | Limit_Clause,
        ALL             = 0xFF
    };

    IOrmCondition();
    ~IOrmCondition() = default;

public:
    IOrmCondition& where(const QString& clause);

    template<typename T>
    IOrmCondition& whereIn(const QString& field, const QList<T>& range, Relation relation = And_Type);

    template<typename T>
    IOrmCondition& whereBetween(const QString& field, const QPair<T, T>& range, Relation relation = And_Type);
    IOrmCondition& whereBetween(const QString& field, QVariant lowerBound, QVariant upperBound, Relation relation = And_Type);

    IOrmCondition& whereLike(const QString& field, const QString& value, Relation relation = And_Type);

    IOrmCondition& whereEndWith(const QString& field, const QString& value, Relation relation = And_Type);

    IOrmCondition& whereStartWith(const QString& field, const QString& value, Relation relation = And_Type);

    IOrmCondition& whereContain(const QString& field, const QString& value, Relation relation = And_Type);

    IOrmCondition& whereNotLike(const QString& field, const QString& value, Relation relation = And_Type);

    IOrmCondition& whereIsNull(const QString& field, Relation relation = And_Type);

    IOrmCondition& whereIsNotNull(const QString& field, Relation relation = And_Type);

    IOrmCondition& whereEqual(const QString& field, const QVariant& value, Relation relation = And_Type);

    IOrmCondition& whereNotEqual(const QString& field, const QVariant& value, Relation relation = And_Type);

    IOrmCondition& whereLessThan(const QString& field, const QVariant& value, Relation relation = And_Type);

    IOrmCondition& whereLessEqual(const QString& field, const QVariant& value, Relation relation = And_Type);

    IOrmCondition& whereGreatThan(const QString& field, const QVariant& value, Relation relation = And_Type);

    IOrmCondition& whereGreatEqual(const QString& field, const QVariant& value, Relation relation = And_Type);

    IOrmCondition& whereTrue();

    IOrmCondition& whereFalse();

public:
    IOrmCondition& having(const QString& clause);      //! @note this is not field. its clause

    template<typename T>
    IOrmCondition& havingIn(const QString& field, const QList<T>& range, Relation relation = And_Type);

    template<typename T>
    IOrmCondition& havingBetween(const QString& field, const QPair<qint8, qint8>& range, Relation relation = And_Type);
    IOrmCondition& havingBetween(const QString& field, const QVariant& lowerBound, const QVariant& upperBound, Relation relation = And_Type);

    IOrmCondition& havingEqual(const QString& field, const QVariant& value, Relation relation = And_Type);

    IOrmCondition& havingNotEqual(const QString& field, const QVariant& value, Relation relation = And_Type);

    IOrmCondition& havingLessThan(const QString& field, const QVariant& value, Relation relation = And_Type);

    IOrmCondition& havingLessEqual(const QString& field, const QVariant& value, Relation relation = And_Type);

    IOrmCondition& havingGreatThan(const QString& field, const QVariant& value, Relation relation = And_Type);

    IOrmCondition& havingGreatEqual(const QString& field, const QVariant& value, Relation relation = And_Type);

//    IOrmCondition& havingLike(const QString& field, const QString& value, Relation relation = And_Type);

//    IOrmCondition& havingEndWith(const QString& field, const QString& value, Relation relation = And_Type);

//    IOrmCondition& havingStartWith(const QString& field, const QString& value, Relation relation = And_Type);

//    IOrmCondition& havingContain(const QString& field, const QString& value, Relation relation = And_Type);

//    IOrmCondition& havingNotLike(const QString& field, const QString& value, Relation relation = And_Type);

//    IOrmCondition& havingIsNull(const QString& field, Relation relation = And_Type);

//    IOrmCondition& havingIsNotNull(const QString& field, Relation relation = And_Type);

public:
    IOrmCondition& conditionAnd(IOrmCondition condition);

    IOrmCondition& conditionOr(IOrmCondition condition);

    IOrmCondition& conditionAndNot(IOrmCondition condition);

    IOrmCondition& conditionOrNot(IOrmCondition condition);

    static IOrmCondition& conditionNot(IOrmCondition& condition);

    IOrmCondition& orderByAsc(const QString& field);

    IOrmCondition& orderByDesc(const QString& field);

    IOrmCondition& groupBy(const QString& field);

    IOrmCondition& limit(IOrmDialectWare* dialect, quint64 count);

    IOrmCondition& limit(IOrmDialectWare* dialect, quint64 start, quint64 count);

public:
    QString toSql(Type types = IOrmCondition::Default) const;

    QString toWhereClause() const;
    QString toOrderByClause() const;
    QString toGroupByClause() const;
    QString toLimitClause() const;
    QString toHavingClause() const;

    QMap<QString, QVariant> getParameters() const;  // only for test use
    void bindParameters(ISqlQuery& query) const;
    void bindParameters(QSqlQuery& query) const;
    bool isValid() const;

private:
    friend class IOrmConditionImpl;
    std::shared_ptr<IOrmConditionImpl> impl;
};


namespace IOrmConditionHelper{
    void whereIn(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QList<qint8>& range, IOrmCondition::Relation relation = IOrmCondition::And_Type);
    void whereIn(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QList<quint8>& range, IOrmCondition::Relation relation = IOrmCondition::And_Type);
    void whereIn(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QList<qint16>& range, IOrmCondition::Relation relation = IOrmCondition::And_Type);
    void whereIn(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QList<quint16>& range, IOrmCondition::Relation relation = IOrmCondition::And_Type);
    void whereIn(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QList<qint32>& range, IOrmCondition::Relation relation = IOrmCondition::And_Type);
    void whereIn(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QList<quint32>& range, IOrmCondition::Relation relation = IOrmCondition::And_Type);
    void whereIn(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QList<quint64>& range, IOrmCondition::Relation relation = IOrmCondition::And_Type);
    void whereIn(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QList<qint64>& range, IOrmCondition::Relation relation = IOrmCondition::And_Type);
    void whereIn(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QList<float>& range, IOrmCondition::Relation relation = IOrmCondition::And_Type);
    void whereIn(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QList<double>& range, IOrmCondition::Relation relation = IOrmCondition::And_Type);
    void whereIn(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QList<QString>& range, IOrmCondition::Relation relation = IOrmCondition::And_Type);
    void whereIn(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QList<QVariant>& range, IOrmCondition::Relation relation = IOrmCondition::And_Type);
    void whereIn(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QList<QDate>& range, IOrmCondition::Relation relation = IOrmCondition::And_Type);
    void whereIn(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QList<QTime>& range, IOrmCondition::Relation relation = IOrmCondition::And_Type);
    void whereIn(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QList<QDateTime>& range, IOrmCondition::Relation relation = IOrmCondition::And_Type);
    void whereIn(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QStringList& range, IOrmCondition::Relation relation = IOrmCondition::And_Type);

    void whereBetween(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QPair<qint8, qint8>& range, IOrmCondition::Relation relation = IOrmCondition::And_Type);
    void whereBetween(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QPair<quint8, quint8>& range, IOrmCondition::Relation relation = IOrmCondition::And_Type);
    void whereBetween(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QPair<qint16, qint16>& range, IOrmCondition::Relation relation = IOrmCondition::And_Type);
    void whereBetween(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QPair<quint16, quint16>& range, IOrmCondition::Relation relation = IOrmCondition::And_Type);
    void whereBetween(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QPair<qint32, qint32>& range, IOrmCondition::Relation relation = IOrmCondition::And_Type);
    void whereBetween(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QPair<quint32, quint32>& range, IOrmCondition::Relation relation = IOrmCondition::And_Type);
    void whereBetween(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QPair<qint64, qint64>& range, IOrmCondition::Relation relation = IOrmCondition::And_Type);
    void whereBetween(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QPair<quint64, quint64>& range, IOrmCondition::Relation relation = IOrmCondition::And_Type);
    void whereBetween(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QPair<float, float>& range, IOrmCondition::Relation relation = IOrmCondition::And_Type);
    void whereBetween(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QPair<double, double>& range, IOrmCondition::Relation relation = IOrmCondition::And_Type);
    void whereBetween(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QPair<QString, QString>& range, IOrmCondition::Relation relation = IOrmCondition::And_Type);
    void whereBetween(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QPair<QVariant, QVariant>& range, IOrmCondition::Relation relation = IOrmCondition::And_Type);
    void whereBetween(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QPair<QDate, QDate>& range, IOrmCondition::Relation relation = IOrmCondition::And_Type);
    void whereBetween(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QPair<QTime, QTime>& range, IOrmCondition::Relation relation = IOrmCondition::And_Type);
    void whereBetween(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QPair<QDateTime, QDateTime>& range, IOrmCondition::Relation relation = IOrmCondition::And_Type);

    void havingIn(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QList<qint8>& range, IOrmCondition::Relation relation = IOrmCondition::And_Type);
    void havingIn(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QList<quint8>& range, IOrmCondition::Relation relation = IOrmCondition::And_Type);
    void havingIn(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QList<qint16>& range, IOrmCondition::Relation relation = IOrmCondition::And_Type);
    void havingIn(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QList<quint16>& range, IOrmCondition::Relation relation = IOrmCondition::And_Type);
    void havingIn(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QList<qint32>& range, IOrmCondition::Relation relation = IOrmCondition::And_Type);
    void havingIn(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QList<quint32>& range, IOrmCondition::Relation relation = IOrmCondition::And_Type);
    void havingIn(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QList<quint64>& range, IOrmCondition::Relation relation = IOrmCondition::And_Type);
    void havingIn(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QList<qint64>& range, IOrmCondition::Relation relation = IOrmCondition::And_Type);
    void havingIn(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QList<float>& range, IOrmCondition::Relation relation = IOrmCondition::And_Type);
    void havingIn(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QList<double>& range, IOrmCondition::Relation relation = IOrmCondition::And_Type);
    void havingIn(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QList<QString>& range, IOrmCondition::Relation relation = IOrmCondition::And_Type);
    void havingIn(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QList<QVariant>& range, IOrmCondition::Relation relation = IOrmCondition::And_Type);
    void havingIn(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QList<QDate>& range, IOrmCondition::Relation relation = IOrmCondition::And_Type);
    void havingIn(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QList<QTime>& range, IOrmCondition::Relation relation = IOrmCondition::And_Type);
    void havingIn(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QList<QDateTime>& range, IOrmCondition::Relation relation = IOrmCondition::And_Type);
    void havingIn(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QStringList& range, IOrmCondition::Relation relation = IOrmCondition::And_Type);

    void havingBetween(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QPair<qint8, qint8>& range, IOrmCondition::Relation relation = IOrmCondition::And_Type);
    void havingBetween(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QPair<quint8, quint8>& range, IOrmCondition::Relation relation = IOrmCondition::And_Type);
    void havingBetween(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QPair<qint16, qint16>& range, IOrmCondition::Relation relation = IOrmCondition::And_Type);
    void havingBetween(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QPair<quint16, quint16>& range, IOrmCondition::Relation relation = IOrmCondition::And_Type);
    void havingBetween(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QPair<qint32, qint32>& range, IOrmCondition::Relation relation = IOrmCondition::And_Type);
    void havingBetween(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QPair<quint32, quint32>& range, IOrmCondition::Relation relation = IOrmCondition::And_Type);
    void havingBetween(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QPair<qint64, qint64>& range, IOrmCondition::Relation relation = IOrmCondition::And_Type);
    void havingBetween(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QPair<quint64, quint64>& range, IOrmCondition::Relation relation = IOrmCondition::And_Type);
    void havingBetween(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QPair<float, float>& range, IOrmCondition::Relation relation = IOrmCondition::And_Type);
    void havingBetween(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QPair<double, double>& range, IOrmCondition::Relation relation = IOrmCondition::And_Type);
    void havingBetween(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QPair<QString, QString>& range, IOrmCondition::Relation relation = IOrmCondition::And_Type);
    void havingBetween(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QPair<QVariant, QVariant>& range, IOrmCondition::Relation relation = IOrmCondition::And_Type);
    void havingBetween(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QPair<QDate, QDate>& range, IOrmCondition::Relation relation = IOrmCondition::And_Type);
    void havingBetween(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QPair<QTime, QTime>& range, IOrmCondition::Relation relation = IOrmCondition::And_Type);
    void havingBetween(std::shared_ptr<IOrmConditionImpl> impl, const QString& field, const QPair<QDateTime, QDateTime>& range, IOrmCondition::Relation relation = IOrmCondition::And_Type);
}

template<typename T>
IOrmCondition& IOrmCondition::whereIn(const QString& field, const QList<T>& range, IOrmCondition::Relation relation)
{
    IOrmConditionHelper::whereIn(impl, field, range, relation);
    return *this;
}

template<typename T>
IOrmCondition& IOrmCondition::whereBetween(const QString& field, const QPair<T, T>& range, IOrmCondition::Relation relation)
{
    IOrmConditionHelper::whereBetween(impl, field, range, relation);
    return *this;
}

template<typename T>
IOrmCondition& IOrmCondition::havingIn(const QString& field, const QList<T>& range, IOrmCondition::Relation relation)
{
    IOrmConditionHelper::havingIn(impl, field, range, relation);
    return *this;
}

template<typename T>
IOrmCondition& IOrmCondition::havingBetween(const QString& field, const QPair<qint8, qint8>& range, IOrmCondition::Relation relation)
{
    IOrmConditionHelper::havingBetween(impl, field, range, relation);
    return *this;
}

#define $Cdt IOrmCondition()

$PackageWebCoreEnd
