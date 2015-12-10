#include "repository.h"
#include <QDebug>

using namespace std;

Repository::Repository()
{
    if(QSqlDatabase::contains(constants::CONNECTION_NAME))
        {
            db = QSqlDatabase::database(constants::CONNECTION_NAME);
        }
        else
        {
            db = QSqlDatabase::addDatabase("QSQLITE", constants::CONNECTION_NAME);
            db.setDatabaseName(constants::DATABASE_NAME);
            db.open();
        }
    /* Býr til töflur ef þær eru ekki til fyrir
     *
     */
        QSqlQuery query(db);
        query.exec(constants::CREATE_SCIENTISTS_TABLE);
        query.exec(constants::CREATE_COMPUTERS_TABLE);
        query.exec(constants::CREATE_OWNERS_TABLE);
}

vector<Scientist> Repository::open_scientist_db(QString sql_command)
{
    vector<Scientist> data;
    QSqlQuery query(db);
    query.exec(sql_command);

    while (query.next())
    {
        string first, last;
        QDate b, d;
        bool g, a, act;
        int id_n;
        first = query.value("firstname").toString().toStdString();
        last = query.value("lastname").toString().toStdString();
        b = QDate::fromString(query.value("birth").toString(), constants::IMPORT_DATE_FORMAT);
        d = QDate::fromString(query.value("death").toString(), constants::IMPORT_DATE_FORMAT);
        id_n = query.value("id").toInt();
        g = query.value("gender").toBool();
        a = query.value("alive").toBool();
        act = query.value("active").toBool();
        Scientist temp(first, last, g, b, d, a, id_n, act);
        data.push_back(temp);
    }
    query.exec(constants::SCIENTIST_JOIN);
    return data;
}

vector<Computers> Repository::open_computer_db(QString sql_command)
{
    vector<Computers> data;
    QSqlQuery query(db);
    query.exec(sql_command);
    while (query.next())
    {
        string name;
        int year, id_n;
        bool b;
        int ct;

        name = query.value("name").toString().toStdString();
        ct = (query.value("type").toInt());
        year = query.value("built_year").toInt();
        id_n = query.value("id").toInt();
        b = query.value("built").toBool();
        Computers temp(name, year, b, ct, id_n);
        data.push_back(temp);
    }
    return data;    
}

void Repository::add_scientist(Scientist s)
{
    QSqlQuery query(db);
    query.prepare(constants::INSERT_FORM);
    query.bindValue(":first", QString::fromStdString(s.get_first()));
    query.bindValue(":last", QString::fromStdString(s.get_last()));
    query.bindValue(":b", s.get_birth());
    query.bindValue(":d", s.get_death());
    query.bindValue(":g", s.get_gender());
    query.bindValue(":a", s.get_living());
    query.bindValue(":act", 1);
    query.exec();

}

void Repository::add_computer(Computers c)
{
    QSqlQuery query(db);
    query.prepare(constants::INSERT_COMPUTER);
    query.bindValue(":name", QString::fromStdString(c.get_name()));
    if (c.get_year())
    {
        query.bindValue(":by", c.get_year());
    }
    else
    {
        query.bindValue(":by", "NULL");
    }
    query.bindValue(":type", c.get_type());
    query.bindValue(":built", c.get_built());
    query.exec();
}

vector<string> Repository::connected(QString command, QString column)
{
    vector<string> data;
    QSqlQuery query(db);
    query.exec(command);
    while (query.next())
    {
        string name;
        name = query.value(column).toString().toStdString();
        data.push_back(name);
    }
    return data;
}

vector<Scientist> Repository::connected_to_delete(QString command)
{
    vector<Scientist> data;
    QSqlQuery query(db);
    query.exec(command);
    Scientist temp;
    while (query.next())
    {
        string name;
        int id;
        name = query.value("lastname").toString().toStdString();
        id = query.value("scientist_id").toInt();
        temp.set_last(name);
        temp.set_id(id);
        data.push_back(temp);
    }
    return data;
}

void Repository::edit_remove(QString command)
{
    QSqlQuery query(db);
    query.exec(command);
}

