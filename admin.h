#ifndef ADMIN_H
#define ADMIN_H

#include <QString>

class Admin {
public:
    Admin(int admin_id);
    Admin(QString email);
    int get_id();
    QString get_email();
    bool check_passwort(QString passwort);
    bool set_email(QString neue_email);
    bool set_passwort(QString neuers_passwort);
private:
    int id;
};

#endif // ADMIN_H
