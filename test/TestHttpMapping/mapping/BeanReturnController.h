#pragma once

#include <IWebCore>

class BeanReturnController : public IControllerInterface<BeanReturnController>
{
    Q_GADGET
    $AsController(BeanReturnController)
public:
    BeanReturnController() = default;

    $GetMapping(getBean, getBean)
    IJsonResponse getBean();

    $GetMapping(getBeans, getBeans)
    IJsonResponse getBeans();

    $GetMapping(getBeans_1, getBeans_1)
    IJsonResponse getBeans_1();

    $GetMapping(getBeans_vector, getVectorBeans)
    IJsonResponse getBeans_vector();

    $GetMapping(getListString, getListString)
    IJsonResponse getListString();

    $GetMapping(getListInt, getListInt)
    IJsonResponse getListInt();

    $GetMapping(getListBool, getListBool)
    IJsonResponse getListBool();

    $GetMapping(getBeansMap, getBeansMap)
    IJsonResponse getBeansMap();

    $GetMapping(getBeansListMap, getBeansListMap)
    IJsonResponse getBeansListMap();

    $GetMapping(getPlainText, getPlainTextBean)
    IPlainTextResponse getPlainText();

    // NOTE: 不能使用 QString 以外的数据类型
//    $GetMapping(getBeansIntMap, getBeansIntMap)
//    IJsonResponse getBeansIntMap();

};

