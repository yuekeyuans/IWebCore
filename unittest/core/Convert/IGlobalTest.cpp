#include "IGlobalTest.h"
#include <core/util/IConvertUtil2.h>

IGlobalTest::IGlobalTest()
{

}

void IGlobalTest::slotTest1()
{
    qDebug() << IConvertUtil2::convertTo<bool>(QString("false")).value();
}
