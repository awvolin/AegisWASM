#include "config.h"
#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString cssFile = "/home/alexvolin/Documents/qt3/css/newSheet.css";
    QString db = QDir::homePath() + "/path/to/your/data/mydb.db";

    QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName(db);



    if (!mydb.open())
    {
        qDebug() << "Database Connection Failed";
        //return 0;
    }

    MainWindow w;
    w.show();
    return a.exec();


}
