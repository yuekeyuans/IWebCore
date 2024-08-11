#include <ICore/IApplication>
#include "NameBean.h"
#include "PersonBean.h"

int main(int argc, char *argv[])
{
//    NameBean bean;
//    qDebug() << bean.toJson();

    PersonBean person;

    qDebug() << person.toJson();
}
