#ifndef ARBEIT_H
#define ARBEIT_H

#include <QString>
#include "dozent.h"

class Arbeit {
public:
    Arbeit(int arbeit_id);
    int get_id();
    int get_typ();
    QString get_typ_as_QString();
    QString get_titel();
    Dozent* get_betreuer();
    QString get_bearbeiter();
    int get_bearbeitungsstatus();
    QString get_bearbeitungsstatus_as_QString();
    QString get_studiengang();
    QString get_stichwortliste();
    QString get_erlauterung();
    QString get_von();
    QString get_bis();
    QString get_firma();
    QString get_semester();
    bool set_typ(int neuer_typ);
    bool set_titel(QString neuer_titel);
    bool set_bearbeiter(QString neuer_bearbeiter);
    bool set_bearbeitungsstatus(int neuer_bearbeitungsstatus);
    bool set_studiengang(QString neuer_studiengang);
    bool set_stichwortliste(QString neue_stichwortliste);
    bool set_erlauterung(QString neue_erlauterung);
    bool set_von(QString neues_von);
    bool set_bis(QString neues_bis);
    bool set_firma(QString neue_firma);
    bool set_semester(QString neues_semester);
    bool delete_arbeit();
private:
    int id;
};

#endif // ARBEIT_H
