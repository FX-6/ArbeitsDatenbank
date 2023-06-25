#include "logindock.h"
#include "ui_logindock.h"

#include "admin.h"
#include "dozent.h"

LoginDock::LoginDock(DBAccess *db, QWidget *parent) : QDockWidget(parent), ui(new Ui::LoginDock), db(db) {
    ui->setupUi(this);
}

LoginDock::~LoginDock() {
    delete ui;
}

void LoginDock::on_login_admin_pushButton_clicked() {
    try {
        Admin admin(ui->email_admin_lineEdit->text());
        if (admin.check_passwort(ui->passwort_admin_lineEdit->text())) {
            emit login_as_admin(admin.get_id(), this);
        } else {
            ui->error_admin_label->setText("Passwort falsch");
        }
    } catch (int error) {
        ui->error_admin_label->setText("Admin existiert nicht");
    }
}

void LoginDock::on_login_dozent_pushButton_clicked() {
    try {
        Dozent dozent(ui->email_dozent_lineEdit->text());
        if (dozent.get_login_versuche() >= 3) {
            ui->error_dozent_label->setText("Account gesperrt (Zu viele Fehlversuche)");
        } else if (dozent.check_passwort(ui->passwort_dozent_lineEdit->text())) {
            emit login_as_dozent(dozent.get_id(), this);
        } else {
            ui->error_dozent_label->setText("Passwort falsch, " + QString::number(3 - dozent.get_login_versuche()) + " Versuche übrig");
        }
    } catch (int error) {
        ui->error_dozent_label->setText("Dozent existiert nicht");
    }
}
