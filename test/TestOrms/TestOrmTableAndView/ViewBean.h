#pragma once

#include <IWebCore>

class ViewBean : public IOrmViewInterface<ViewBean>
{
    Q_GADGET
    $AsView(ViewBean)

public:
    ViewBean();

    $ViewFieldDeclare(int, age)
    int age{100};
};
