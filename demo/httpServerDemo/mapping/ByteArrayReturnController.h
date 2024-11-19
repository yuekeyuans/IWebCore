﻿#pragma once

#include <QtCore>
#include <IWebCore>

class ByteArrayReturnController : public IControllerInterface
{
    Q_GADGET
    $AsController(ByteArrayReturnController);
public:
    ByteArrayReturnController();

    $GetMapping(getArray1, array1)
    QString getArray1(IResponse& response);

    $GetMapping(getArray2, array2)
    IByteArrayResponse getArray2();

    $GetMapping(getArray3, array3)
    QByteArray getArray3();

    $GetMapping(getArray4, array4)
    void getArray4(IResponse& response);
};

$RegisterController(ByteArrayReturnController)
