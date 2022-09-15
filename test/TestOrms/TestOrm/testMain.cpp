#include <QtTest>
#include <IWebCore>

//#include "MysqlDatabase.h"
//#include "SqliteDatabase.h"
//#include "TestOrm.h"
//#include "TestDatabase.h"

//#include "TestOrmSelect.h"
//#include "TestOrmUpdate.h"
//#include "TestOrmUtil.h"

//#include "TestSqliteOnlyDatbase.h"
//#include "MySqlWorldDatabase.h"

//#include "condition/TestConditionOrderBy.h"
//#include "condition/TestOrmCondition.h"
//#include "condition/TestConditionLimit.h"
//#include "condition/TestConditionWhere.h"

//#include "types/TestOrmBool.h"
//#include "types/TestOrmDateTime.h"
//#include "types/TestOrmNumber.h"
//#include "types/TestOrmPrimaryKey.h"

int main(int argc, char** argv)
{
    ITaskManage::run(argc, argv);

    ITestManage::invokeAllTestClass();
}
