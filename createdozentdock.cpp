#include "createdozentdock.h"
#include "ui_createdozentdock.h"

#include "dozent.h"

CreateDozentDock::CreateDozentDock(DBAccess *db, QWidget *parent) : QDockWidget(parent), ui(new Ui::CreateDozentDock), db(db) {
    // Setup UI
    ui->setupUi(this);
}

CreateDozentDock::~CreateDozentDock() {
    // Delete UI
    delete ui;
}

void CreateDozentDock::on_erstellen_pushButton_clicked() {
    // Clear label
    ui->error_label->setText("");

    // Check for input
    if (ui->nachname_lineEdit->text() == "" || ui->vorname_lineEdit->text() == "" || ui->email_lineEdit->text() == "" || ui->passwort_lineEdit->text() == "" || ui->passwort_wiederholt_lineEdit->text() == "") {
        ui->error_label->setText("Bitte alles ausfüllen");
        return;
    }

    // Check if email is unique
    try {
        Dozent(ui->email_lineEdit->text());
        ui->error_label->setText("E-Mail existiert bereits");
        return;
    } catch (int e) {}

    // Check passwort
    if (ui->passwort_lineEdit->text() != ui->passwort_wiederholt_lineEdit->text()) {
        ui->error_label->setText("Passwöter sind nicht gleich");
        return;
    }

    // Create dozent
    if (db->create_dozent(ui->nachname_lineEdit->text(), ui->vorname_lineEdit->text(), ui->email_lineEdit->text(), ui->passwort_lineEdit->text())) {
        this->hide();
        delete this;
    } else {
        ui->error_label->setText("Fehler beim Erstellen des Dozenten");
    }
}
