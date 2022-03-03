#pragma once

#include <IWebCore>

class ViewBean : public IOrmViewInterface<ViewBean>
{
    Q_GADGET
    $AsView(ViewBean)

public:
    static const IOrmViewInfo& viewInfo() {
        static IOrmViewInfo m_viewInfo(staticMetaObject);
        return m_viewInfo;
    }
    virtual const IOrmViewInfo& getViewInfo() const final{
        return viewInfo();
    }

public:
    ViewBean();

    $ViewFieldDeclare(int, age)
    int age{100};
};
