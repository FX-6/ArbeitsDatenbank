#include "admin.h"

#include <QtSql/QSqlQuery>

Admin::Admin(int admin_id) : id(admin_id) {}

Admin::Admin(QString email) {
    QSqlQuery query;
    query.prepare("SELECT admin_id FROM admins WHERE email = ? LIMIT 1;");
    query.addBindValue(email);
    query.exec();
    if (!query.first()) {
        throw 0;
    }
    this->id = query.value(0).toInt();
}

int Admin::get_id() {
    return this->id;
}

QString Admin::get_email() {
    QSqlQuery query;
    query.prepare("SELECT email FROM admins WHERE admin_id = ? LIMIT 1;");
    query.addBindValue(this->id);
    query.exec();
    query.first();
    return query.value(0).toString();
}

bool Admin::check_passwort(QString passwort) {
    QSqlQuery query;
    query.prepare("SELECT passwort FROM admins WHERE admin_id = ? LIMIT 1;");
    query.addBindValue(this->id);
    query.exec();
    query.first();
    return passwort == query.value(0).toString();
}

bool Admin::set_email(QString neue_email) {
    QSqlQuery query;
    query.prepare("UPDATE admins SET email = ? WHERE admin_id = ?");
    query.addBindValue(neue_email);
    query.addBindValue(this->id);
    return query.exec();
}

bool Admin::set_passwort(QString neues_passwort) {
    QSqlQuery query;
    query.prepare("UPDATE admins SET passwort = ? WHERE admin_id = ?");
    query.addBindValue(neues_passwort);
    query.addBindValue(this->id);
    return query.exec();
}
