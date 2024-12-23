#include "BasicArgument.h"

BasicArgument::BasicArgument()
{
}

QString BasicArgument::headerTypeInt(int $Header(MyInt))
{
    return QString::number(MyInt);
}

QString BasicArgument::headerType(IString $Header(MyHeader))
{
    return MyHeader.toQString();
}
