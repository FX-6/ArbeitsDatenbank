#ifndef DOZENT_H
#define DOZENT_H

#include <QString>

class Dozent
{
public:
    Dozent(int dozenten_id);
    Dozent(QString email);
    int get_id();
    QString get_vorname();
    QString get_nachname();
    QString get_name();
    QString get_email();
    bool check_passwort(QString passwort);
    int get_login_versuche();
    bool get_muss_passwort_andern();
    bool set_vorname(QString neuer_vorname);
    bool set_nachname(QString neuer_nachname);
    bool set_email(QString neue_email);
    bool set_passwort(QString neues_passwort);
    bool set_login_versuche(int neue_anzahl);
    bool set_muss_passwort_andern(bool neure_wert);
    bool delete_dozent();
private:
    int id;
};

#endif // DOZENT_H
