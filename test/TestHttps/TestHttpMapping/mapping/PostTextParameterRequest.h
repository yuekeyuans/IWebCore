#pragma once

#include <IWeb/IControllerInterface>

// all kind of text
class PostTextParameterRequest : public IHttpControllerInterface<PostTextParameterRequest>
{
    Q_GADGET
    $AsController(PostTextParameterRequest)
public:
    PostTextParameterRequest();

    // 发现一个bug, 就是这个名称和函数必须对的上，不然就会出现错误

    $PostMapping(postTextPlain, /postText1)
    QString postTextPlain($Content(QString, name));

    // 字符串转 int
    $PostMapping(postText2, /postText2)
    QString postText2($Content(int, value));

    // 字符串转 double
    $PostMapping(postText3, /postText3)
    QString postText3($Content(double, value));

    // 字符串转 jsonObject
    $PostMapping(postText4, /postText4)
    QString postText4($Content(QJsonObject, value));

    // 字符串转 jsonValue
    $PostMapping(postText5, /postText5)
    QString postText5($Content(QJsonValue, value));

    $PostMapping(postText6, /postText6)
    QString postText6($Content(qlonglong, value));
};


