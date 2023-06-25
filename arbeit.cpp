#include "arbeit.h"

#include <QtSql/QSqlQuery>

Arbeit::Arbeit(int arbeit_id) : id(arbeit_id) {}

int Arbeit::get_id() {
    return this->id;
}

int Arbeit::get_typ() {
    QSqlQuery query;
    query.prepare("SELECT typ FROM arbeiten WHERE arbeit_id = ? LIMIT 1;");
    query.addBindValue(this->id);
    query.exec();
    query.first();
    return query.value(0).toInt();
}

QString Arbeit::get_typ_as_QString() {
    QSqlQuery query;
    query.prepare("SELECT typ FROM arbeiten WHERE arbeit_id = ? LIMIT 1;");
    query.addBindValue(this->id);
    query.exec();
    query.first();
    switch (query.value(0).toInt()) {
    case 0:
        return "Bachelorarbeit (Abschlussarbeit)";
    case 1:
        return "Masterarbeit (Abschlussarbeit)";
    case 2:
        return "IN-Projekt (Bachelor)";
    case 3:
        return "IS-Projekt (Bachelor)";
    case 4:
        return "MI-Projekt (Bachelor)";
    case 5:
        return "SE-Projekt (Bachelor)";
    case 6:
        return "Master-Projekt";
    case 7:
    default:
        return "Sonstiges Projekt";
    }
}

QString Arbeit::get_titel() {
    QSqlQuery query;
    query.prepare("SELECT titel FROM arbeiten WHERE arbeit_id = ? LIMIT 1;");
    query.addBindValue(this->id);
    query.exec();
    query.first();
    return query.value(0).toString();
}

Dozent* Arbeit::get_betreuer() {
    QSqlQuery query;
    query.prepare("SELECT betreuer FROM arbeiten WHERE arbeit_id = ? LIMIT 1;");
    query.addBindValue(this->id);
    query.exec();
    query.first();
    return new Dozent(query.value(0).toInt());
}

QString Arbeit::get_bearbeiter() {
    QSqlQuery query;
    query.prepare("SELECT bearbeiter FROM arbeiten WHERE arbeit_id = ? LIMIT 1;");
    query.addBindValue(this->id);
    query.exec();
    query.first();
    return query.value(0).toString();
}

int Arbeit::get_bearbeitungsstatus() {
    QSqlQuery query;
    query.prepare("SELECT bearbeitungsstatus FROM arbeiten WHERE arbeit_id = ? LIMIT 1;");
    query.addBindValue(this->id);
    query.exec();
    query.first();
    return query.value(0).toInt();
}

QString Arbeit::get_bearbeitungsstatus_as_QString() {
    QSqlQuery query;
    query.prepare("SELECT bearbeitungsstatus FROM arbeiten WHERE arbeit_id = ? LIMIT 1;");
    query.addBindValue(this->id);
    query.exec();
    query.first();
    if (query.value(0).toInt() == 0) {
        return "In Arbeit";
    } else {
        return "Abgeschlossen";
    }
}

QString Arbeit::get_studiengang() {
    QSqlQuery query;
    query.prepare("SELECT studiengang FROM arbeiten WHERE arbeit_id = ? LIMIT 1;");
    query.addBindValue(this->id);
    query.exec();
    query.first();
    return query.value(0).toString();
}

QString Arbeit::get_stichwortliste() {
    QSqlQuery query;
    query.prepare("SELECT stichwortliste FROM arbeiten WHERE arbeit_id = ? LIMIT 1;");
    query.addBindValue(this->id);
    query.exec();
    query.first();
    return query.value(0).toString();
}

QString Arbeit::get_erlauterung() {
    QSqlQuery query;
    query.prepare("SELECT erlauterung FROM arbeiten WHERE arbeit_id = ? LIMIT 1;");
    query.addBindValue(this->id);
    query.exec();
    query.first();
    return query.value(0).toString();
}

QString Arbeit::get_von() {
    QSqlQuery query;
    query.prepare("SELECT von FROM arbeiten WHERE arbeit_id = ? LIMIT 1;");
    query.addBindValue(this->id);
    query.exec();
    query.first();
    return query.value(0).toString();
}

QString Arbeit::get_bis() {
    QSqlQuery query;
    query.prepare("SELECT bis FROM arbeiten WHERE arbeit_id = ? LIMIT 1;");
    query.addBindValue(this->id);
    query.exec();
    query.first();
    return query.value(0).toString();
}

QString Arbeit::get_firma() {
    QSqlQuery query;
    query.prepare("SELECT firma FROM arbeiten WHERE arbeit_id = ? LIMIT 1;");
    query.addBindValue(this->id);
    query.exec();
    query.first();
    return query.value(0).toString();
}

QString Arbeit::get_semester() {
    QSqlQuery query;
    query.prepare("SELECT semester FROM arbeiten WHERE arbeit_id = ? LIMIT 1;");
    query.addBindValue(this->id);
    query.exec();
    query.first();
    return query.value(0).toString();
}

bool Arbeit::set_typ(int neuer_typ) {
    QSqlQuery query;
    query.prepare("UPDATE arbeiten SET typ = ? WHERE arbeit_id = ?;");
    query.addBindValue(neuer_typ);
    query.addBindValue(this->id);
    return query.exec();
}

bool Arbeit::set_titel(QString neuer_titel) {
    QSqlQuery query;
    query.prepare("UPDATE arbeiten SET titel = ? WHERE arbeit_id = ?;");
    query.addBindValue(neuer_titel);
    query.addBindValue(this->id);
    return query.exec();
}

bool Arbeit::set_bearbeiter(QString neuer_bearbeiter) {
    QSqlQuery query;
    query.prepare("UPDATE arbeiten SET bearbeiter = ? WHERE arbeit_id = ?;");
    query.addBindValue(neuer_bearbeiter);
    query.addBindValue(this->id);
    return query.exec();
}

bool Arbeit::set_bearbeitungsstatus(int neuer_bearbeitungsstatus) {
    QSqlQuery query;
    query.prepare("UPDATE arbeiten SET bearbeitungsstatus = ? WHERE arbeit_id = ?;");
    query.addBindValue(neuer_bearbeitungsstatus);
    query.addBindValue(this->id);
    return query.exec();
}

bool Arbeit::set_studiengang(QString neuer_studiengang) {
    QSqlQuery query;
    query.prepare("UPDATE arbeiten SET studiengang = ? WHERE arbeit_id = ?;");
    query.addBindValue(neuer_studiengang);
    query.addBindValue(this->id);
    return query.exec();
}

bool Arbeit::set_stichwortliste(QString neue_stichwortliste) {
    QSqlQuery query;
    query.prepare("UPDATE arbeiten SET stichwortliste = ? WHERE arbeit_id = ?;");
    query.addBindValue(neue_stichwortliste);
    query.addBindValue(this->id);
    return query.exec();
}

bool Arbeit::set_erlauterung(QString neue_erlauterung) {
    QSqlQuery query;
    query.prepare("UPDATE arbeiten SET erlauterung = ? WHERE arbeit_id = ?;");
    query.addBindValue(neue_erlauterung);
    query.addBindValue(this->id);
    return query.exec();
}

bool Arbeit::set_von(QString neues_von) {
    QSqlQuery query;
    query.prepare("UPDATE arbeiten SET von = ? WHERE arbeit_id = ?;");
    query.addBindValue(neues_von);
    query.addBindValue(this->id);
    return query.exec();
}

bool Arbeit::set_bis(QString neues_bis) {
    QSqlQuery query;
    query.prepare("UPDATE arbeiten SET bis = ? WHERE arbeit_id = ?;");
    query.addBindValue(neues_bis);
    query.addBindValue(this->id);
    return query.exec();
}

bool Arbeit::set_firma(QString neue_firma) {
    QSqlQuery query;
    query.prepare("UPDATE arbeiten SET firma = ? WHERE arbeit_id = ?;");
    query.addBindValue(neue_firma);
    query.addBindValue(this->id);
    return query.exec();
}

bool Arbeit::set_semester(QString neuer_semester) {
    QSqlQuery query;
    query.prepare("UPDATE arbeiten SET semester = ? WHERE arbeit_id = ?;");
    query.addBindValue(neuer_semester);
    query.addBindValue(this->id);
    return query.exec();
}

bool Arbeit::delete_arbeit() {
    QSqlQuery query;
    query.prepare("DELETE FROM arbeiten WHERE arbeit_id = ?;");
    query.addBindValue(this->id);
    return query.exec();
}
