#pragma once

#include <IWebCore>

class NumberBean : public IOrmTableInterface<NumberBean>
{
    Q_GADGET
    $AsTable(NumberBean)
public:
    NumberBean() = default;

    $AutoGenerate(id)
    $PrimaryKey(id)
    $Column(qlonglong, id)

//    $Column(char, a);
//    $Column(uchar, b);
    $Column(short, c);
    $Column(ushort, d);
    $Column(int, e);
    $Column(uint, f);
    $Column(long, g);
    $Column(ulong, h);
    $Column(qlonglong, i);
    $Column(qulonglong, j);

    $Column(float, k);
    $Column(double, l);
};


