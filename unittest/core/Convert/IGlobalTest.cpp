#include "IGlobalTest.h"
#include <core/util/IConvertUtil2.h>

IGlobalTest::IGlobalTest()
{

}

void IGlobalTest::slotTest1()
{
    qDebug() << IConvertUtil2::convertTo<bool>(QString("false")).value();
    qDebug() << IConvertUtil2::convertTo<bool>("true").value();
    qDebug() << IConvertUtil2::convertTo<bool>(QByteArray("true")).value();
    qDebug() << IConvertUtil2::convertTo<bool>(IStringView("true")).value();
    qDebug() << IConvertUtil2::convertTo<QString>(true);
    qDebug() << IConvertUtil2::convertTo<QString>(false);
    qDebug() << IConvertUtil2::convertTo<QString>(100);
}
