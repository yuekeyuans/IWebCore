#include "TestConditionWhere.h"

TestConditionWhere::TestConditionWhere()
{

}

void TestConditionWhere::init()
{

}

void TestConditionWhere::test_length()
{
    qDebug() << cityModel.count() << endl;
    qDebug() << cityModel.findOneByPriamaryKey(1) << endl;

    qDebug() << countryModel.count() << endl;
    qDebug() << countryModel.findOneByPriamaryKey("BDI") << endl;
}

void TestConditionWhere::test_where1()
{
    auto table = countryModel.findOne(IOrmCondition().orderByDesc(CountryTable::field_Population).limit(countryModel.getDialect(), 1));
    QTEST_ASSERT(table.Code == "CHN");

    table = countryModel.findOne($Cdt
                                 .whereBetween(CountryTable::field_GNP, 0, 100)
                                 .orderByAsc(CountryTable::field_GNP)
                                 .limit(countryModel.getDialect(), 1));

    qDebug() << countryModel.findColumns({CountryTable::field_Region}, $Cdt.groupBy(CountryTable::field_Region));
}
