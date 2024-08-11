#include <ICore/IApplication>
#include "NameBean.h"

int main(int argc, char *argv[])
{
    NameBean bean;
    qDebug() << bean.toJson();
}
