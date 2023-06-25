#include "DBAccess.h"

#include <iostream>
#include <QtSql/QSqlQuery>

DBAccess::DBAccess(QString db_name) {
    // Open DataBase
    this->db = QSqlDatabase::addDatabase("QSQLITE");
    this->db.setDatabaseName(db_name);
    if (!db.open()) {
        std::cerr << "Datenbank konnte nicht geöffnet werden." << std::endl;
        exit(2);
    }
}

void DBAccess::setup_database() {
    // Create admins TABLE
    QSqlQuery("CREATE TABLE IF NOT EXISTS admins ("
              "    admin_id INTEGER NOT NULL,"
              "    email TEXT NOT NULL UNIQUE,"
              "    passwort TEXT NOT NULL,"
              "    PRIMARY KEY(admin_id));");
    // Create dozenten TABLE
    QSqlQuery("CREATE TABLE IF NOT EXISTS dozenten ("
              "    dozent_id INTEGER NOT NULL,"
              "    email TEXT NOT NULL UNIQUE,"
              "    passwort TEXT NOT NULL,"
              "    vorname TEXT NOT NULL,"
              "    nachname TEXT NOT NULL,"
              "    login_versuche INT NOT NULL DEFAULT 0,"
              "    muss_passwort_andern INT NOT NULL DEFAULT 1,"
              "    PRIMARY KEY(dozent_id)"
              "    CHECK (muss_passwort_andern IN (0, 1)));");
    // CREATE arbeiten TABLE
    QSqlQuery("CREATE TABLE IF NOT EXISTS arbeiten ("
              "    arbeit_id INTEGER NOT NULL,"
              "    typ INTEGER NOT NULL,"
              "    titel TEXT NOT NULL,"
              "    betreuer INTEGER NOT NULL,"
              "    bearbeiter TEXT NOT NULL,"
              "    bearbeitungsstatus INTEGER NOT NULL,"
              "    studiengang TEXT NOT NULL,"
              "    stichwortliste TEXT,"
              "    erlauterung TEXT,"
              "    von TEXT,"
              "    bis TEXT,"
              "    firma TEXT,"
              "    semester TEXT,"
              "    PRIMARY KEY(arbeit_id),"
              "    FOREIGN KEY(betreuer) REFERENCES dozenten(dozent_id),"
              "    CHECK (typ IN (0, 1, 2, 3, 4, 5, 6, 7)),"
              "    CHECK (bearbeitungsstatus IN (0, 1)));");
    // Inser admin
    QSqlQuery("INSERT OR IGNORE INTO admins(email, passwort) VALUES ('Admin', 'nimdA');");
}

void DBAccess::reset_database() {
    // Drop TABLEs
    QSqlQuery("DROP TABLE IF EXISTS admins;");
    QSqlQuery("DROP TABLE IF EXISTS dozenten;");
    QSqlQuery("DROP TABLE IF EXISTS arbeiten;");
    // Setup DataBase
    this->setup_database();
}

void DBAccess::test_database() {
    // Insert dozenten
    QSqlQuery("INSERT OR IGNORE INTO dozenten(dozent_id, email, passwort, vorname, nachname) VALUES"
              "    (1, 'rd@hs.aa', 'RD', 'Roland', 'Dietrich'),"
              "    (2, 'km@hs.aa', 'CH', 'Christian', 'Heinlein'),"
              "    (3, 'dk@hs.aa', 'DK', 'Detlef', 'Küpper');");
    // Insert arbeiten
    QSqlQuery("INSERT OR IGNORE INTO arbeiten(betreuer, typ, bearbeiter, titel, stichwortliste, erlauterung, bearbeitungsstatus, studiengang, firma) VALUES"
              "    (1, 0, 'Max Maier', 'Codegenerierung mit Enterprise Architect', 'Softwareentwicklung, Modellierung', NULL, 1, 'IN-SE', NULL),"
              "    (1, 1, 'Moritz Busch', 'Testautomatisierung für Getriebesteuerung', 'Automotive, Softwaretest', NULL, 1, 'IN-SE', 'Bosch'),"
              "    (1, 5, 'Frieda Bolte', 'Schichtenarchitektur mit Qt', 'Softwareentwicklung, Softwarearchitektur', 'Beispiel: Seminarverwaltung', 1, 'IN-SE', NULL),"
              "    (1, 7, 'Paul Lämple', 'E-Motion Motorsteuerung', 'Automotive, E-Mobilität', 'Wahlprojekt, IN4', 1, 'IN-SE', 'E-Motion-Rennteam der Hochschule'),"
              "    (3, 0, 'Franz Großbier', 'Datenbanken für die Software-Versionierung', 'Softwareentwicklung, Konfigurationsmanagement, SQL', NULL, 1, 'IN-SE', NULL),"
              "    (3, 1, 'Fritz Klein', 'Intelligente lernende Agenten', 'Künstliche Intelligenz', NULL, 1, 'IN-SE', NULL),"
              "    (3, 4, 'Hans Schmidt', 'Gestaltungsaspekte von grafischen Benutzeroberflächen', 'Mensch-Maschine-Kommunikation', 'Demobeispiel mit Qt5', 1, 'IN-MI', NULL),"
              "    (3, 6, 'Heiner Müller', 'NoSQL-Datenbanken vs. Relationale Datenbanken - Sinnvolle Einsatzzenarien', 'SQL, Relationenmodell, MongoDB, MySQL', NULL, 1, 'IN-SE', NULL),"
              "    (2, 0, 'Maria Kurz', 'Ein 2-Pass-Compiler für MOSTflexiPL', 'Funktionale Programmiersprache', 'Abgebrochen', 1, 'IN-SE', NULL),"
              "    (2, 1, 'Ulrike Lang', 'Ein 2-Pass-Compiler für MOSTflexiPL', 'Funktionale Programmiersprache', NULL, 1, 'IN-SE', NULL),"
              "    (2, 5, 'Ulrich Frei', 'Funktionale Programmiersprachen im Vergleich', 'Haskell, Lisp, MOSTflexiPL, Quick-Sort, Insert-Sort, Tree-Sort', 'Anwendungsbeispiele: verschiedene Suchalgorithmen', 1, 'IN-SE', NULL),"
              "    (2, 5, 'Martin Fromm', 'Abstrakte Datentypen in MOSTflexiPL', 'Stack, List, Queue, Tree, Graph', 'Programmbibliothek mit klassischen ADTs', 1, 'IN-SE', NULL);");
}

QList<Dozent> DBAccess::get_dozentent() {
    // Create QList
    QList dozenten = QList<Dozent>();

    // Query
    QSqlQuery query;
    query.prepare("SELECT dozent_id FROM dozenten;");
    query.exec();

    // Populate QList
    while (query.next()) {
        dozenten.append(Dozent(query.value(0).toInt()));
    }

    // return QList
    return dozenten;
}

QList<Arbeit> DBAccess::get_arbeiten() {
    // Create QList
    QList arbeiten = QList<Arbeit>();

    // Query
    QSqlQuery query;
    query.prepare("SELECT arbeit_id FROM arbeiten;");
    query.exec();

    // Populate QList
    while (query.next()) {
        arbeiten.append(Arbeit(query.value(0).toInt()));
    }

    // return QList
    return arbeiten;
}

bool DBAccess::create_dozent(QString nachname, QString vorname, QString email, QString passwort) {
    QSqlQuery query;
    query.prepare("INSERT OR IGNORE INTO dozenten(nachname, vorname, email, passwort) VALUES (?, ?, ?, ?);");
    query.addBindValue(nachname);
    query.addBindValue(vorname);
    query.addBindValue(email);
    query.addBindValue(passwort);
    return query.exec();
}

bool DBAccess::create_arbeit(int typ, QString titel, int betreuer, QString bearbeiter, int bearbeitungsstatus, QString studiengang) {
    QSqlQuery query;
    query.prepare("INSERT OR IGNORE INTO arbeiten(typ, titel, betreuer, bearbeiter, bearbeitungsstatus, studiengang) VALUES (?, ?, ?, ?, ?, ?);");
    query.addBindValue(typ);
    query.addBindValue(titel);
    query.addBindValue(betreuer);
    query.addBindValue(bearbeiter);
    query.addBindValue(bearbeitungsstatus);
    query.addBindValue(studiengang);
    return query.exec();
}
