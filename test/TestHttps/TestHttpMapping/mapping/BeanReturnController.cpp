#include "BeanReturnController.h"

#include "mapping/TestBean.h"

IJsonResponse BeanReturnController::getBean()
{
    TestBean bean;
    return bean.toJson();
}

IJsonResponse BeanReturnController::getBeans()
{
    QList<TestBean> beans;
    TestBean bean;
    bean.name = "hello world";
    beans.append(bean);
    beans.append(TestBean{});
    return IConvertUtil::toJsonValue(beans);
}

IJsonResponse BeanReturnController::getBeans_1()
{
    QList<TestBean> beans;
    TestBean bean;
    bean.name = "hello world";
    beans.append(bean);
    beans.append(TestBean{});
    return beans;
}

IJsonResponse BeanReturnController::getBeans_vector()
{
    QVector<TestBean> beans;
    beans.append(TestBean{});
    beans.append(TestBean{});
    return beans;
}

IJsonResponse BeanReturnController::getListString()
{
    QList<QString> strings;
    strings << "hello" << "world";
    return strings;
}

IJsonResponse BeanReturnController::getListInt()
{
    QList<int> list;
    list << 1 << 2 << 3;
    return list;
}

IJsonResponse BeanReturnController::getListBool()
{
    QList<bool> bools;
    bools << true << false << true;
    return bools;
}

IJsonResponse BeanReturnController::getBeansMap()
{
    QMap<QString, TestBean> beans;
    beans["hello"] = TestBean{};
    beans["world"] = TestBean{};
    return beans;
}

IJsonResponse BeanReturnController::getBeansListMap()
{
    QList<QMap<QString, TestBean>> beans;
    QMap<QString, TestBean> map;
    map["hello"] = TestBean{};
    beans.append(map);
    return beans;
}

IPlainTextResponse BeanReturnController::getPlainText()
{
    QList<QMap<QString, TestBean>> beans;
    QMap<QString, TestBean> map;
    map["hello"] = TestBean{};
    beans.append(map);
    return beans;
}

//IJsonResponse BeanReturnController::getBeansIntMap()
//{
//    QMap<int,TestBean> beans;
//    beans.insert(0, TestBean{});
//    beans.insert(1, TestBean{});
//    return beans;
//}
