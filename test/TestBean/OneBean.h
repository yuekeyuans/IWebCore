#pragma once

#include <IWebCore>

class OneBean : public IBeanInterface<OneBean>
{
    Q_GADGET
    $AsBean(OneBean)
public:
    OneBean();

    $BeanField(int, id);

    $BeanFieldDeclare(QString, name)
    QString name = "yuekeyuan";
};

