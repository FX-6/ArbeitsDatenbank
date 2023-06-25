#ifndef DBACCESS_H
#define DBACCESS_H

#include <QString>
#include <QtSql/QSqlDatabase>

#include "dozent.h"
#include "arbeit.h"

class DBAccess {
public:
    DBAccess(QString db_name);
    void setup_database();
    void reset_database();
    void test_database();
    QList<Dozent> get_dozentent();
    QList<Arbeit> get_arbeiten();
    bool create_dozent(QString nachname, QString vorname, QString email, QString passwort);
    bool create_arbeit(int typ, QString titel, int betreuer, QString bearbeiter, int bearbeitungssstatus, QString studiengang);
private:
    QSqlDatabase db;
};

#endif // DBACCESS_H
