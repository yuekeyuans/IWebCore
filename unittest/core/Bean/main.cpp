#include <ICore/IApplication>
#include <ICore/IContext>
#include "NameBean.h"
#include "PersonBean.h"


$EnableTaskOutput(true)

int main(int argc, char *argv[])
{
    bool ok;
    NameBean bean;
    qDebug() << bean.toJson(&ok) << ok;

    PersonBean person;

    qDebug() << person.toJson(&ok) << ok;

//    PersonBean bean2;
}
