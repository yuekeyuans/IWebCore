#include <QtTest>

#include "MysqlDatabase.h"
#include "SqliteDatabase.h"
#include "TestOrm.h"
#include "TestDatabase.h"

#include "TestOrmSelect.h"
#include "TestOrmUpdate.h"
#include "TestOrmUtil.h"

#include "TestSqliteOnlyDatbase.h"
#include "MySqlWorldDatabase.h"


#include "condition/TestConditionOrderBy.h"
#include "condition/TestOrmCondition.h"
#include "condition/TestConditionLimit.h"
#include "condition/TestConditionWhere.h"

#include "types/TestOrmBool.h"
#include "types/TestOrmDateTime.h"
#include "types/TestOrmNumber.h"
#include "types/TestOrmPrimaryKey.h"
#include <IWebCore>

int main(int argc, char** argv)
{
    ITaskManage::run(argc, argv);
    $ITestBegin

    $ITestClass(TestSqliteOnlyDatbase)

    $ITestClass(TestOrmPrimaryKey)
    $ITestClass(TestOrmNumber)
    $ITestClass(TestOrmDateTime)
    $ITestClass(TestOrmBool)

    $ITestClass(TestOrmUtil);
    $ITestClass(TestOrmUpdate);
    $ITestClass(TestOrmSelect);
    $ITestClass(TestOrm);
    $ITestClass(TestDatabase)

    $ITestClass(TestOrmCondition)
    $ITestClass(TestConditionOrderBy)
    $ITestClass(TestConditionWhere)


    $ITestEnd
}
