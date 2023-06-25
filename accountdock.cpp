#include "accountdock.h"
#include "ui_accountdock.h"

#include <iostream>

AccountDock::AccountDock(Dozent *dozent, QWidget *parent) : QDockWidget(parent), ui(new Ui::AccountDock), dozent(dozent) {
    // Setup UI
    ui->setupUi(this);

    // Adjust visibility of UI Elements
    ui->loschen_pushButton->hide();
    ui->info_label->hide();
    ui->aktuelles_passwort_lineEdit->hide();
    ui->neues_passwort_lineEdit->hide();
    ui->neues_passwort_wiederholt_lineEdit->hide();

    // Set og values
    this->og_nachname = dozent->get_nachname();
    this->og_vorname = dozent->get_vorname();
    this->og_email = dozent->get_email();

    // Set UI values
    ui->nachname_lineEdit->setText(this->og_nachname);
    ui->vorname_lineEdit->setText(this->og_vorname);
    ui->email_lineEdit->setText(this->og_email);
}

AccountDock::AccountDock(Admin *admin, Dozent *dozent, QWidget *parent) : QDockWidget(parent), ui(new Ui::AccountDock), dozent(dozent), admin(admin) {
    // Setup UI
    ui->setupUi(this);

    if (dozent != nullptr) {
        // Adjust visibility of UI Elements
        ui->info_label->hide();
        ui->aktuelles_passwort_lineEdit->hide();
        ui->neues_passwort_lineEdit->hide();
        ui->neues_passwort_wiederholt_lineEdit->hide();

        // Set og values
        this->og_nachname = dozent->get_nachname();
        this->og_vorname = dozent->get_vorname();
        this->og_email = dozent->get_email();

        // Set UI values
        ui->nachname_lineEdit->setText(this->og_nachname);
        ui->vorname_lineEdit->setText(this->og_vorname);
        ui->email_lineEdit->setText(this->og_email);

        std::cout << "Dozent: " << dozent->get_name().toStdString() << " " << dozent->get_id() << std::endl;
    } else {
        // Adjust visibility of UI Elements
        ui->nachname_lineEdit->hide();
        ui->vorname_lineEdit->hide();
        ui->email_lineEdit->setDisabled(true);
        ui->loschen_pushButton->hide();
        ui->info_label->hide();
        ui->aktuelles_passwort_lineEdit->hide();
        ui->neues_passwort_lineEdit->hide();
        ui->neues_passwort_wiederholt_lineEdit->hide();

        // Set og values
        this->og_nachname = "";
        this->og_vorname = "";
        this->og_email = admin->get_email();

        // Set UI values
        ui->nachname_lineEdit->setText(this->og_nachname);
        ui->vorname_lineEdit->setText(this->og_vorname);
        ui->email_lineEdit->setText(this->og_email);
    }
}

AccountDock::~AccountDock() {
    // Delete UI
    delete ui;
}

void AccountDock::on_email_lineEdit_textEdited(const QString &arg1) {
    // Adjust visibility of UI Elements
    if (arg1 == this->og_email && !ui->neues_passwort_lineEdit->isVisible()) {
        ui->info_label->hide();
        ui->aktuelles_passwort_lineEdit->hide();
        ui->neues_passwort_lineEdit->hide();
        ui->neues_passwort_wiederholt_lineEdit->hide();
    } else if (arg1 != this->og_email) {
        ui->info_label->show();
        ui->aktuelles_passwort_lineEdit->show();
    }
}

void AccountDock::on_passwort_andern_pushButton_clicked() {
    // Adjust visibility of UI Elements
    ui->info_label->show();
    ui->aktuelles_passwort_lineEdit->show();
    ui->neues_passwort_lineEdit->show();
    ui->neues_passwort_wiederholt_lineEdit->show();
}

void AccountDock::on_loschen_pushButton_clicked() {
    if (this->dozent->delete_dozent()) {
        delete this->dozent;
        this->hide();
        delete this;
    } else {
        ui->error_label->setText(ui->error_label->text() + "Fehler beim löschen. ");
    }
}

void AccountDock::on_bestatigen_pushButton_clicked() {
    // Clear error
    ui->error_label->setText("");

    // Handle vorname change
    QString neuer_vorname = ui->vorname_lineEdit->text();
    if (neuer_vorname != this->og_vorname) {
        this->og_vorname = neuer_vorname;
        this->dozent->set_vorname(neuer_vorname);
        ui->error_label->setText("Vorname geändert. ");
    }

    // Handle nachname change
    QString neuer_nachname = ui->nachname_lineEdit->text();
    if (neuer_nachname != this->og_nachname) {
        this->og_nachname = neuer_nachname;
        this->dozent->set_nachname(neuer_nachname);
        ui->error_label->setText(ui->error_label->text() + "Nachname geändert. ");
    }

    // Check if password is correct
    bool correct_current_passwort = false;
    if (ui->aktuelles_passwort_lineEdit->isVisible() && ui->aktuelles_passwort_lineEdit->text() != "") {
        QString provided_current_passwort = ui->aktuelles_passwort_lineEdit->text();
        if (this->admin != nullptr) {
            correct_current_passwort = this->admin->check_passwort(provided_current_passwort);
        } else if (this->dozent != nullptr) {
            correct_current_passwort = this->dozent->check_passwort(provided_current_passwort);
        }
        if (!correct_current_passwort) {
            ui->error_label->setText(ui->error_label->text() + "Passwort inkorrerkt. ");
        }
    }

    // Handle email change
    QString neue_email = ui->email_lineEdit->text();
    if (neue_email != this->og_email) {
        if (correct_current_passwort) {
            this->og_email = neue_email;
            this->dozent->set_email(neue_email);
            ui->error_label->setText(ui->error_label->text() + "E-Mail geädnert. ");
        }
    }

    // Handle passwort change
    if (ui->neues_passwort_lineEdit->isVisible() && ui->neues_passwort_lineEdit->text() != "") {
        if (correct_current_passwort && ui->neues_passwort_lineEdit->text() == ui->neues_passwort_wiederholt_lineEdit->text()) {
            if (this->dozent != nullptr) {
                this->dozent->set_passwort(ui->neues_passwort_lineEdit->text());
                if (this->admin != nullptr) {
                    this->dozent->set_muss_passwort_andern(true);
                }
            } else {
                this->admin->set_passwort(ui->neues_passwort_lineEdit->text());
            }
            ui->error_label->setText(ui->error_label->text() + "Passwort geädnert. ");
        } else if (correct_current_passwort) {
            ui->error_label->setText(ui->error_label->text() + "Neue Passwöter sind ungleich. ");
        }
    }
}
