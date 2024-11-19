#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initGui();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initGui()
{
   m_sidebar = new SideBar;


   auto mainSpliter = new QSplitter(Qt::Horizontal);
   mainSpliter->addWidget(m_sidebar);
}

