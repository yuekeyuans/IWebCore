#pragma once

#include <IControllerInterface>

class PostParameterController : public IControllerInterface<PostParameterController, true>
{
    Q_GADGET
    $AsController(PostParameterController)

public:
    PostParameterController();

    $GetMapping(p1, /postParam1)
    QString p1(IRequest& request, IResponse& response);

    $PostMapping(p2, /postParam2)
    QString p2(IRequest& request);

    $PostMapping(p3, /postParam3)
    QString p3(IRequest& request);

    $PostMapping(p4, /postParam4)
    QString p4($Content(QJsonValue, value));

    $PostMapping(p5, /postParam5)
    QString p5($Content(QJsonObject, value));

    $PostMapping(p6, /postParam6)
    QString p6($Content(QJsonArray, value));

    // 错误请求，看可能解析
    $PostMapping(p7, /postParam7)
    QString p7($Content(QJsonArray, value));

    $PostMapping(p8, /postParam8)
    QString p8($Content(QJsonValue&, value));

    $PostMapping(p9, /postParam9)
    QString p9($Body(int&, name));

    $PostMapping(p10, /postParam10)
    QString p10($Body(QString, name));

    $PostMapping(p11, /postParam11)
    QString p11($Body(bool, name));

    $PostMapping(p12, /postParam12)
    QString p12($Body(double, name));

    $PostMapping(p13, /postParam13)
    QString p13($Body(QJsonArray, name));

    $PostMapping(p14, /postParam14)
    QString p14($Body(QJsonObject, name));

};


