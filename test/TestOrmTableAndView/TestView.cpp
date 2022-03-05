#include "TestView.h"

TestView::TestView()
{

}

void TestView::test_viewFind()
{
    auto list = model.findAll();
    qDebug() << IConvertUtil::toString(list);
    QTEST_ASSERT(!list.isEmpty());
}
