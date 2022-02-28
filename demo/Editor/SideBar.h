#pragma once

#include <QWidget>

namespace Ui {
class SideBar;
}

class SideBar : public QWidget
{
    Q_OBJECT

public:
    explicit SideBar(QWidget *parent = nullptr);
    ~SideBar();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::SideBar *ui;
};

