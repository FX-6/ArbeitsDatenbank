#include "arbeitdock.h"

#include "ui_arbeitdock.h"

ArbeitDock::ArbeitDock(Arbeit *arbeit, QWidget *parent) : QDockWidget(parent), ui(new Ui::ArbeitDock), arbeit(arbeit) {
    // Setup UI
    ui->setupUi(this);

    // Adjust UI
    ui->titel_lineEdit->setDisabled(true);
    ui->typ_comboBox->setDisabled(true);
    ui->bearbeiter_lineEdit->setDisabled(true);
    ui->status_comboBox->setDisabled(true);
    ui->studiengang_lineEdit->setDisabled(true);
    ui->stichwort_lineEdit->setDisabled(true);
    ui->erlauterung_lineEdit->setDisabled(true);
    ui->von_lineEdit->setDisabled(true);
    ui->bis_lineEdit->setDisabled(true);
    ui->firma_lineEdit->setDisabled(true);
    ui->semester_lineEdit->setDisabled(true);
    ui->error_label->hide();
    ui->loschen_pushButton->hide();
    ui->speichern_pushButton->hide();

    // Set og values
    this->og_typ = arbeit->get_typ();
    this->og_titel = arbeit->get_titel();
    this->og_bearbeiter = arbeit->get_bearbeiter();
    this->og_status = arbeit->get_bearbeitungsstatus();
    this->og_studiengang = arbeit->get_studiengang();
    this->og_stichwortliste = arbeit->get_stichwortliste();
    this->og_erlauterung = arbeit->get_erlauterung();
    this->og_von = arbeit->get_von();
    this->og_bis = arbeit->get_bis();
    this->og_firma = arbeit->get_firma();
    this->og_semester = arbeit->get_semester();

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

    // Set UI values
    ui->titel_lineEdit->setText(this->og_titel);
    int typ_index = ui->typ_comboBox->findData(this->og_typ);
    ui->typ_comboBox->setCurrentIndex(typ_index);
    ui->betreuer_label->setText(arbeit->get_betreuer()->get_name());
    ui->bearbeiter_lineEdit->setText(this->og_bearbeiter);
    int status_index = ui->status_comboBox->findData(this->og_status);
    ui->status_comboBox->setCurrentIndex(status_index);
    ui->studiengang_lineEdit->setText(this->og_studiengang);
    ui->stichwort_lineEdit->setText(this->og_stichwortliste);
    ui->erlauterung_lineEdit->setText(this->og_erlauterung);
    ui->von_lineEdit->setText(this->og_von);
    ui->bis_lineEdit->setText(this->og_bis);
    ui->firma_lineEdit->setText(this->og_firma);
    ui->semester_lineEdit->setText(this->og_semester);
}

ArbeitDock::ArbeitDock(Arbeit *arbeit, Dozent *dozent, QWidget *parent) : QDockWidget(parent), ui(new Ui::ArbeitDock), arbeit(arbeit), dozent(dozent) {
    // Setup UI
    ui->setupUi(this);

    // Nicht eigene Arbeit
    if (arbeit->get_betreuer()->get_id() != dozent->get_id()) {
        // Adjust UI
        ui->titel_lineEdit->setDisabled(true);
        ui->typ_comboBox->setDisabled(true);
        ui->bearbeiter_lineEdit->setDisabled(true);
        ui->status_comboBox->setDisabled(true);
        ui->studiengang_lineEdit->setDisabled(true);
        ui->stichwort_lineEdit->setDisabled(true);
        ui->erlauterung_lineEdit->setDisabled(true);
        ui->von_lineEdit->setDisabled(true);
        ui->bis_lineEdit->setDisabled(true);
        ui->firma_lineEdit->setDisabled(true);
        ui->semester_lineEdit->setDisabled(true);
        ui->error_label->hide();
        ui->loschen_pushButton->hide();
        ui->speichern_pushButton->hide();
    }

    // Set og values
    this->og_typ = arbeit->get_typ();
    this->og_titel = arbeit->get_titel();
    this->og_bearbeiter = arbeit->get_bearbeiter();
    this->og_status = arbeit->get_bearbeitungsstatus();
    this->og_studiengang = arbeit->get_studiengang();
    this->og_stichwortliste = arbeit->get_stichwortliste();
    this->og_erlauterung = arbeit->get_erlauterung();
    this->og_von = arbeit->get_von();
    this->og_bis = arbeit->get_bis();
    this->og_firma = arbeit->get_firma();
    this->og_semester = arbeit->get_semester();

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

    // Set UI values
    ui->titel_lineEdit->setText(this->og_titel);
    int typ_index = ui->typ_comboBox->findData(this->og_typ);
    ui->typ_comboBox->setCurrentIndex(typ_index);
    ui->betreuer_label->setText(arbeit->get_betreuer()->get_name());
    ui->bearbeiter_lineEdit->setText(this->og_bearbeiter);
    int status_index = ui->status_comboBox->findData(this->og_status);
    ui->status_comboBox->setCurrentIndex(status_index);
    ui->studiengang_lineEdit->setText(this->og_studiengang);
    ui->stichwort_lineEdit->setText(this->og_stichwortliste);
    ui->erlauterung_lineEdit->setText(this->og_erlauterung);
    ui->von_lineEdit->setText(this->og_von);
    ui->bis_lineEdit->setText(this->og_bis);
    ui->firma_lineEdit->setText(this->og_firma);
    ui->semester_lineEdit->setText(this->og_semester);
}

ArbeitDock::~ArbeitDock() {
    // Delete UI
    delete ui;
}

void ArbeitDock::on_loschen_pushButton_clicked() {
    // Clear error label
    ui->error_label->setText("");

    // Delete arbeit
    if (this->arbeit->delete_arbeit()) {
        delete this->arbeit;
        this->hide();
        delete this;
    } else {
        ui->error_label->setText("Fehler beim Löschen der Arbeit");
    }
}

void ArbeitDock::on_speichern_pushButton_clicked() {
    // Clear error label
    ui->error_label->setText("");

    // Change arbeit
    QString neuer_titel = ui->titel_lineEdit->text();
    if (neuer_titel != "" && neuer_titel != og_titel) {
        og_titel = neuer_titel;
        this->arbeit->set_titel(neuer_titel);
        ui->error_label->setText(ui->error_label->text() + "Titel geändert. ");
    }

    if (ui->typ_comboBox->currentData().isValid() && ui->typ_comboBox->currentData().toInt() != og_typ) {
        og_typ = ui->typ_comboBox->currentData().toInt();
        this->arbeit->set_typ(ui->typ_comboBox->currentData().toInt());
        ui->error_label->setText(ui->error_label->text() + "Typ geändert. ");
    }

    QString neuer_bearbeiter = ui->bearbeiter_lineEdit->text();
    if (neuer_bearbeiter != "" && neuer_bearbeiter != og_bearbeiter) {
        og_bearbeiter = neuer_bearbeiter;
        this->arbeit->set_bearbeiter(neuer_bearbeiter);
        ui->error_label->setText(ui->error_label->text() + "Bearbeiter geändert. ");
    }

    if (ui->status_comboBox->currentData().isValid() && ui->status_comboBox->currentData().toInt() != og_status) {
        og_status = ui->status_comboBox->currentData().toInt();
        this->arbeit->set_bearbeitungsstatus(ui->status_comboBox->currentData().toInt());
        ui->error_label->setText(ui->error_label->text() + "Status geändert. ");
    }

    QString neuer_studiengang = ui->studiengang_lineEdit->text();
    if (neuer_studiengang != "" && neuer_studiengang != og_studiengang) {
        og_studiengang = neuer_studiengang;
        this->arbeit->set_studiengang(neuer_studiengang);
        ui->error_label->setText(ui->error_label->text() + "Studiengang geändert. ");
    }

    QString neue_stichworte = ui->stichwort_lineEdit->text();
    if (neue_stichworte != og_stichwortliste) {
        og_stichwortliste = neue_stichworte;
        this->arbeit->set_stichwortliste(neue_stichworte);
        ui->error_label->setText(ui->error_label->text() + "Stichworte geändert. ");
    }

    QString neue_erlauterung = ui->erlauterung_lineEdit->text();
    if (neue_erlauterung != og_erlauterung) {
        og_erlauterung = neue_erlauterung;
        this->arbeit->set_erlauterung(neue_erlauterung);
        ui->error_label->setText(ui->error_label->text() + "Erläuterung geändert. ");
    }

    QString neues_von = ui->von_lineEdit->text();
    if (neues_von != og_von) {
        og_von = neues_von;
        this->arbeit->set_von(neues_von);
        ui->error_label->setText(ui->error_label->text() + "Von geändert. ");
    }

    QString neues_bis = ui->bis_lineEdit->text();
    if (neues_bis != og_bis) {
        og_bis = neues_bis;
        this->arbeit->set_bis(neues_bis);
        ui->error_label->setText(ui->error_label->text() + "Bis geändert. ");
    }

    QString neue_firma = ui->firma_lineEdit->text();
    if (neue_firma != og_firma) {
        og_firma = neue_firma;
        this->arbeit->set_firma(neue_firma);
        ui->error_label->setText(ui->error_label->text() + "Firma geändert. ");
    }

    QString neues_semester = ui->semester_lineEdit->text();
    if (neues_semester != og_semester) {
        og_semester = neues_semester;
        this->arbeit->set_semester(neues_semester);
        ui->error_label->setText(ui->error_label->text() + "Smester geändert. ");
    }
}
