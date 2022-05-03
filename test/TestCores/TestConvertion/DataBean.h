#pragma once

#include <IWebCore>

class DataBean : public IBeanInterface<DataBean>
{
    Q_GADGET
    $AsBean(DataBean);
public:
    DataBean();

    $BeanFieldDeclare(int, id);
    int id = 10;

    $BeanFieldDeclare(QString, name);
    QString name = "yuekeyuan";
};

