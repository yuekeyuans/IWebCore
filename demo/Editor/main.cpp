#include "MainWindow.h"

#include <IWebCore>
#include <QtGui>
#include <QApplication>
#include "orm/SqliteDatabase.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    $RegisterDatabase(SqliteDatabase)

    SqliteDatabase::openDatabase("helloworld1.db");
    SqliteDatabase::openDatabase("helloworld2.db");
    SqliteDatabase::openDatabase("helloworld3.db");


    MainWindow w;
    w.show();
    return a.exec();
}
