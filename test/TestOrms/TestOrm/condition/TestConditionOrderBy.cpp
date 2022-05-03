#include "TestConditionOrderBy.h"

TestConditionOrderBy::TestConditionOrderBy()
{

}

void TestConditionOrderBy::test1()
{
    IOrmCondition condition;
    qDebug() << condition.toSql();
}
