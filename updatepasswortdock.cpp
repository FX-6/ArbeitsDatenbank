#include "updatepasswortdock.h"
#include "ui_updatepasswortdock.h"

UpdatePasswortDock::UpdatePasswortDock(Dozent *dozent, QWidget *parent) : QDockWidget(parent), ui(new Ui::UpdatePasswortDock), dozent(dozent) {
    ui->setupUi(this);
}

UpdatePasswortDock::~UpdatePasswortDock() {
    delete ui;
}

void UpdatePasswortDock::on_andern_pushButton_clicked() {
    QString altes_passwort = ui->altes_passwort_lineEdit->text();
    QString neues_passwort = ui->neues_passwort_lineEdit->text();
    QString neues_passwort_wiederholt = ui->neues_passwort_wiederholt_lineEdit->text();

    if (neues_passwort != neues_passwort_wiederholt) {
        ui->error_label->setText("Neue Passwörter stimmen nicht überein");
        return;
    }

    if (this->dozent->get_login_versuche() >= 3) {
        ui->error_label->setText("Account gesperrt (Zu viele Fehlversuche)");
        this->setFeatures(QDockWidget::DockWidgetClosable);
        return;
    }

    if (!this->dozent->check_passwort(altes_passwort)) {
        ui->error_label->setText("Altes Passwort falsch, " + QString::number(3 - this->dozent->get_login_versuche()) + " Versuche übrig");
        return;
    }

    this->dozent->set_passwort(neues_passwort);
    this->hide();
    delete this;
}
