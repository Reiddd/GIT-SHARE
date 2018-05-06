#include "tableeditor.h"
#include <QApplication>
#include <QSqlQuery>
#include <QObject>

static bool createConnection()
{
/* ------- open database ------- */
    if(!QSqlDatabase::drivers().contains("QSQLITE")){
        QMessageBox::critical(nullptr, "Cannot open database", "need sqlite support!", QMessageBox::Cancel, QMessageBox::Cancel);
        return false;
    }
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName(":memory:");
    if(!db.open()){
        QMessageBox::critical(nullptr, "Cannot open database", "Unable to establish a database connection!", QMessageBox::Cancel, QMessageBox::Cancel);
        return false;
    }

/* ------- create tables ------- */

    QSqlQuery query;

    query.exec("create table person(id        int primary key,"
                                   "firstname varchar(20),"
                                   "lastname  varchar(20)     )");
    query.exec("insert into person values(101, 'Danny'    , 'Young')");
    query.exec("insert into person values(102, 'Christine', 'Holand')");
    query.exec("insert into person values(103, 'Lars'     , 'Gordon')");
    query.exec("insert into person values(104, 'Roberto'  , 'Robitaille')");
    query.exec("insert into person values(105, 'Maria'    , 'Papadopoulos')");

    query.exec("create table items(id          int primary key,"
                                  "imagefile   int,"
                                  "itemtype    varchar(20),"
                                  "description varchar(100)    )");
    query.exec("insert into items "
               "values(0, 0, 'Qt',"
               "'Qt is a full development framework with tools designed to "
               "streamline the creation of stunning applications and  "
               "amazing user interfaces for desktop, embedded and mobile "
               "platforms.')");
    query.exec("insert into items "
               "values(1, 1, 'Qt Quick',"
               "'Qt Quick is a collection of techniques designed to help "
               "developers create intuitive, modern-looking, and fluid "
               "user interfaces using a CSS & JavaScript like language.')");
    query.exec("insert into items "
               "values(2, 2, 'Qt Creator',"
               "'Qt Creator is a powerful cross-platform integrated "
               "development environment (IDE), including UI design tools "
               "and on-device debugging.')");
    query.exec("insert into items "
               "values(3, 3, 'Qt Project',"
               "'The Qt Project governs the open source development of Qt, "
               "allowing anyone wanting to contribute to join the effort "
               "through a meritocratic structure of approvers and "
               "maintainers.')");

    query.exec("create table images (itemid int, file varchar(20))");
    query.exec("insert into images values(0, 'images/qt-logo.png')");
    query.exec("insert into images values(1, 'images/qt-quick.png')");
    query.exec("insert into images values(2, 'images/qt-creator.png')");
    query.exec("insert into images values(3, 'images/qt-project.png')");

    return true;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if(!createConnection()) return 1;

    TableEditor w("person");
    w.show();

    return a.exec();
}
