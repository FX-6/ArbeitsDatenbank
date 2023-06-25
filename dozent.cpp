#include "dozent.h"

#include <QtSql/QSqlQuery>

#include <iostream>

Dozent::Dozent(int dozenten_id) : id(dozenten_id) {}

Dozent::Dozent(QString email) {
    QSqlQuery query;
    query.prepare("SELECT dozent_id FROM dozenten WHERE email = ? COLLATE NOCASE LIMIT 1;");
    query.addBindValue(email);
    query.exec();
    if (!query.first()) {
        throw 0;
    }
    this->id = query.value(0).toInt();
}

int Dozent::get_id() {
    return this->id;
}

QString Dozent::get_vorname() {
    QSqlQuery query;
    query.prepare("SELECT vorname FROM dozenten WHERE dozent_id = ? LIMIT 1;");
    query.addBindValue(this->id);
    query.exec();
    query.first();
    return query.value(0).toString();
}

QString Dozent::get_nachname() {
    QSqlQuery query;
    query.prepare("SELECT nachname FROM dozenten WHERE dozent_id = ? LIMIT 1;");
    query.addBindValue(this->id);
    query.exec();
    query.first();
    return query.value(0).toString();
}

QString Dozent::get_name() {
    return this->get_nachname() + ", " + this->get_vorname();
}

QString Dozent::get_email() {
    QSqlQuery query;
    query.prepare("SELECT email FROM dozenten WHERE dozent_id = ? LIMIT 1;");
    query.addBindValue(this->id);
    query.exec();
    query.first();
    return query.value(0).toString();
}

bool Dozent::check_passwort(QString passwort) {
    if (this->get_login_versuche() >= 3) {
        return false;
    }

    QSqlQuery query;
    query.prepare("SELECT passwort FROM dozenten WHERE dozent_id = ? LIMIT 1;");
    query.addBindValue(this->id);
    query.exec();
    query.first();

    if (passwort == query.value(0).toString()) {
        this->set_login_versuche(0);
        return true;
    } else {
        this->set_login_versuche(this->get_login_versuche() + 1);
        return false;
    }
}

int Dozent::get_login_versuche() {
    QSqlQuery query;
    query.prepare("SELECT login_versuche FROM dozenten WHERE dozent_id = ? LIMIT 1;");
    query.addBindValue(this->id);
    query.exec();
    query.first();
    return query.value(0).toInt();
}

bool Dozent::get_muss_passwort_andern() {
    QSqlQuery query;
    query.prepare("SELECT muss_passwort_andern FROM dozenten WHERE dozent_id = ? LIMIT 1;");
    query.addBindValue(this->id);
    query.exec();
    query.first();
    return query.value(0).toBool();
}

bool Dozent::set_vorname(QString neuer_vorname) {
    std::cout << "neuer_vorname: " << neuer_vorname.toStdString() << " id: " << this->get_id() << std::endl;

    QSqlQuery query;
    query.prepare("UPDATE dozenten SET vorname = ? WHERE dozent_id = ?;");
    query.addBindValue(neuer_vorname);
    query.addBindValue(this->id);
    return query.exec();
}

bool Dozent::set_nachname(QString neuer_nachname) {
    QSqlQuery query;
    query.prepare("UPDATE dozenten SET nachname = ? WHERE dozent_id = ?;");
    query.addBindValue(neuer_nachname);
    query.addBindValue(this->id);
    return query.exec();
}

bool Dozent::set_email(QString neue_email) {
    QSqlQuery query;
    query.prepare("UPDATE dozenten SET email = ? WHERE dozent_id = ?;");
    query.addBindValue(neue_email);
    query.addBindValue(this->id);
    return query.exec();
}

bool Dozent::set_passwort(QString neues_passwort) {
    QSqlQuery query;
    query.prepare("UPDATE dozenten SET passwort = ?, login_versuche = 0, muss_passwort_andern = 0 WHERE dozent_id = ?;");
    query.addBindValue(neues_passwort);
    query.addBindValue(this->id);
    return query.exec();
}

bool Dozent::set_login_versuche(int neue_anzahl) {
    QSqlQuery query;
    query.prepare("UPDATE dozenten SET login_versuche = ? WHERE dozent_id = ?;");
    query.addBindValue(neue_anzahl);
    query.addBindValue(this->id);
    return query.exec();
}

bool Dozent::set_muss_passwort_andern(bool neuer_wert) {
    QSqlQuery query;
    query.prepare("UPDATE dozenten SET muss_passwort_andern = ? WHERE dozent_id = ?;");
    query.addBindValue(neuer_wert);
    query.addBindValue(this->id);
    return query.exec();
}

bool Dozent::delete_dozent() {
    QSqlQuery query;
    query.prepare("DELETE FROM dozenten WHERE dozent_id = ?;");
    query.addBindValue(this->id);
    return query.exec();
}
