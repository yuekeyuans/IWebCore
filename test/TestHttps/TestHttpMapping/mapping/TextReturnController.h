#pragma once

#include <IControllerInterface>

class TextReturnController : public IControllerInterface<TextReturnController>
{
    Q_GADGET
    $AsController(TextReturnController)
public:
    TextReturnController();

    $GetMapping(text1, text1)
    QString text1();

    $GetMapping(text_1, text_1)
    QString text_1();

    $GetMapping(text2, text2)
    IPlainTextResponse text2();

    $GetMapping(text3, text3)
    IPlainTextResponse text3();

    $GetMapping(text4, text4)
    IPlainTextResponse text4();

    $GetMapping(text5, text5)
    void text5(IResponse& response);
};

