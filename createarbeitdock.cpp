#include "createarbeitdock.h"

#include "ui_createarbeitdock.h"

CreateArbeitDock::CreateArbeitDock(DBAccess *db, Dozent *dozent, QWidget *parent) : QDockWidget(parent), ui(new Ui::CreateArbeitDock), db(db), dozent(dozent) {
    // Setup UI
    ui->setupUi(this);

    // Populate Comboboxes
    // Typ
    ui->typ_comboBox->addItem("Bachelorarbeit (Abschlussarbeit)", 0);
    ui->typ_comboBox->addItem("Masterarbeit (Abschlussarbeit)", 1);
    ui->typ_comboBox->addItem("IN-Projekt (Bachelor)", 2);
    ui->typ_comboBox->addItem("IS-Projekt (Bachelor)", 3);
    ui->typ_comboBox->addItem("MI-Projekt (Bachelor)", 4);
    ui->typ_comboBox->addItem("SE-Projekt (Bachelor)", 5);
    ui->typ_comboBox->addItem("Master-Projekt", 6);
    ui->typ_comboBox->addItem("Sonstiges Projekt", 7);
    // Bearbeitungsstatus
    ui->status_comboBox->addItem("In Arbeit", 0);
    ui->status_comboBox->addItem("Abgeschlossen", 1);
}

CreateArbeitDock::~CreateArbeitDock() {
    // Delete UI
    delete ui;
}

void CreateArbeitDock::on_create_pushButton_clicked() {
    // Clear label
    ui->error_label->setText("");

    // Check for input
    if (!ui->typ_comboBox->currentData().isValid() || ui->titel_lineEdit->text() == "" || ui->bearbeiter_lineEdit->text() == "" || !ui->status_comboBox->currentData().isValid() || ui->studiengang_lineEdit->text() == "") {
        ui->error_label->setText("Bitte alles ausfüllen");
        return;
    }

    // Create arbeit
    if (
        db->create_arbeit(
            ui->typ_comboBox->currentData().toInt(),
            ui->titel_lineEdit->text(),
            dozent->get_id(),
            ui->bearbeiter_lineEdit->text(),
            ui->status_comboBox->currentData().toInt(),
            ui->studiengang_lineEdit->text()
        )
    ) {
        this->hide();
        delete this;
    } else {
        ui->error_label->setText("Fehler beim Erstellen der Arbeit");
    }
}
