#include "TestOrmCondition.h"

TestOrmCondition::TestOrmCondition()
{

}

TestOrmCondition::~TestOrmCondition()
{

}

void TestOrmCondition::test_and()
{
    IOrmCondition condition;
    condition.whereEqual("a", 1).whereLike("b", "1");
    auto str = condition.toSql(IOrmCondition::Where_Clause);
    qDebug() << str;
    QTEST_ASSERT(isMatch(str, "WHERE ((a = :a_*) AND (b LIKE :b_*))"));

}

void TestOrmCondition::test_and1()
{

    IOrmCondition condition;
    condition.whereEqual("a", 1);
    condition.conditionAnd(IOrmCondition().whereLike("b", "1"));
    auto str = condition.toSql(IOrmCondition::Where_Clause);
    qDebug() << str;
    QTEST_ASSERT(isMatch(str, "WHERE ((a = :a_*) AND ((b LIKE :b_*)))"));
}

void TestOrmCondition::test_not()
{
    IOrmCondition condition;
    condition.whereEqual("a", 1);
    condition = IOrmCondition::conditionNot(condition);
    auto str = condition.toSql(IOrmCondition::Where_Clause);
    QTEST_ASSERT(isMatch(str, "WHERE NOT ((a = :a_*))"));
    qDebug() << str;
}

void TestOrmCondition::test_not1()
{
    IOrmCondition condition;
    condition.whereEqual("a", 1).whereLike("b", "da%");
    condition = IOrmCondition::conditionNot(condition);
    auto str = condition.toSql(IOrmCondition::Where_Clause);
    QTEST_ASSERT(isMatch(str, "WHERE NOT ((a = :a_*) AND (b LIKE :b_*))"));
    qDebug() << str;
}

// 双重否定变肯定
void TestOrmCondition::test_not2()
{
    IOrmCondition condition;
    condition.whereEqual("a", 1).whereLike("b", "da%");
    condition = IOrmCondition::conditionNot(IOrmCondition::conditionNot(condition));
    auto str = condition.toSql(IOrmCondition::Where_Clause);
    QTEST_ASSERT(isMatch(str,  "WHERE ((a = :a_*) AND (b LIKE :b_*))"));
    qDebug() << str;
}

void TestOrmCondition::test_not3()
{
    IOrmCondition condition;
    condition.whereEqual("a", 1);
    auto con1 = IOrmCondition().whereLike("b", "2");
    condition.conditionAnd(con1);
    auto str = condition.toSql(IOrmCondition::Where_Clause);
    qDebug() << str;
    QTEST_ASSERT(isMatch(str, "WHERE ((a = :a_*) AND ((b LIKE :b_*)))"));
}

void TestOrmCondition::test_condition1()
{
    IOrmCondition condition;
    condition.conditionAnd(IOrmCondition().whereLike("a", "b"));
    auto str = condition.toSql();
    QTEST_ASSERT(isMatch(str, "WHERE (((a LIKE :a_*)))"));
    qDebug() << str;

    condition.whereEqual("b", "3");
    str = condition.toSql();
    qDebug() << str;
    QTEST_ASSERT(isMatch(str, "WHERE (((a LIKE :a_*)) AND (b = :b_*))"));
}

void TestOrmCondition::test_condition2()
{
    IOrmCondition condition;
    condition.conditionOr(IOrmCondition().whereLike("a", "b"));
    auto str = condition.toSql();
    qDebug() << str;
    QTEST_ASSERT(isMatch(str, "WHERE ((a LIKE :a_*))"));

    condition.whereLike("b", "d");
    str = condition.toSql();
    qDebug() << str;
    QTEST_ASSERT(isMatch(str, "WHERE ((a LIKE :a_*)) AND (b LIKE :b_*)"));

}

void TestOrmCondition::test_condition3()
{
    IOrmCondition condition;
    condition.conditionOrNot(IOrmCondition().whereLike("a", "b"));
    auto str = condition.toSql();
    qDebug() << str;
    QTEST_ASSERT(isMatch(str, "WHERE NOT ((a LIKE :a_*))"));
}

void TestOrmCondition::test_condition4()
{
    IOrmCondition condition;
    condition.conditionAndNot(IOrmCondition().whereLike("a", "b"));
    auto str = condition.toSql();
    qDebug() << str;
    QTEST_ASSERT(isMatch(str, "WHERE (NOT ((a LIKE :a_*)))"));
}

void TestOrmCondition::test_or()
{
    IOrmCondition condition;
    condition.whereEqual("a", 1).whereEqual("b", 43, IOrmCondition::Or_Type);
    auto str = condition.toSql(IOrmCondition::Where_Clause);
    QTEST_ASSERT(isMatch(str, "WHERE ((a = :a_*) OR (b = :b_*))"));
    qDebug() << str;
}

void TestOrmCondition::test_like()
{
    IOrmCondition condition;
    condition.whereLike("a", "a");
    qDebug() << condition.toSql();
    QTEST_ASSERT(condition.getParameters().values().first() == "a");
}

void TestOrmCondition::test_unlike()
{
    IOrmCondition condition;
    condition.whereNotLike("a", "a");
    qDebug() << condition.toSql();
    QTEST_ASSERT(condition.getParameters().values().first() == "a");
}

void TestOrmCondition::test_startWith()
{
    IOrmCondition condition;
    condition.whereStartWith("a", "a");
    qDebug() << condition.toSql();
    QTEST_ASSERT(condition.getParameters().values().first() == "%a");
}

void TestOrmCondition::test_endWith()
{
    IOrmCondition condition;
    condition.whereEndWith("a", "a");
    qDebug() << condition.toSql();
    QTEST_ASSERT(condition.getParameters().values().first() == "a%");
}

void TestOrmCondition::test_contain()
{
    IOrmCondition condition;
    condition.whereContain("a", "a");
    qDebug() << condition.toSql();
    QTEST_ASSERT(condition.getParameters().values().first() == "%a%");
}

void TestOrmCondition::test_multiCondition()
{
    IOrmCondition condition;
    condition.whereLike("a", "1").conditionOr(IOrmCondition().whereEqual("b", 1)).whereLessThan("c", 3);
    auto str = condition.toSql();
    qDebug() << condition.toSql();
    QTEST_ASSERT(isMatch(str, "WHERE ((a LIKE :a_*) OR ((b = :b_*)) AND (c < :c_*))"));
}

bool TestOrmCondition::isMatch(QString str, QString pattern)
{
    pattern.replace("(", "\\(").replace(")", "\\)").replace("*", "[0-9]*");
//    qDebug().noquote() << pattern;
    QRegularExpression exp(pattern);
    if(!exp.isValid()){
        return false;
    }

    return exp.match(str).hasMatch();
}
