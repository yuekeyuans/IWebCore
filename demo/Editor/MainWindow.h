#pragma once


#include <QtWidgets>

#include "SideBar.h"




QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:
    void initGui();

private:
    Ui::MainWindow *ui;


private:
    SideBar* m_sidebar{nullptr};

};
