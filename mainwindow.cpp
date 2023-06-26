#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QListWidgetItem>

#include "updatepasswortdock.h"
#include "accountdock.h"
#include "arbeitdock.h"
#include "createdozentdock.h"
#include "createarbeitdock.h"

MainWindow::MainWindow(DBAccess *db, QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), db(db) {
    // Setup UI
    ui->setupUi(this);

    // Add Arbeiten
    this->refresh_arbeiten_list();

    // Add Dozenten
    this->refresh_dozenten_list();

    // Adjust visibility of UI Elements
    // Navbar - Lower
    ui->dozentensuche_pushButton->hide();
    ui->projektsuche_pushButton->hide();
    ui->dozent_erstellen_pushButton->hide();
    ui->arbeit_erstellen_pushButton->hide();
    ui->account_bearbeiten_pushButton->hide();
    ui->logout_pushButton->hide();
    // Content
    ui->dozenten_listWidget->hide();

    // Populate UI
    QList dozenten = db->get_dozentent();
    for (Dozent dozent : dozenten) {
        ui->betreuer_comboBox->addItem(dozent.get_name(), dozent.get_id());
    }
}

MainWindow::~MainWindow() {
    // Delete UI
    delete ui;
}

void MainWindow::refresh_arbeiten_list() {
    // Clear list
    ui->arbeiten_listWidget->clear();

    // Get arbeiten
    QList arbeiten = db->get_arbeiten();
    for (Arbeit arbeit : arbeiten) {
        // Skip arbeit wenn gefiltert
        if (ui->titel_lineEdit->text() != "" && !arbeit.get_titel().contains(ui->titel_lineEdit->text())) {
            continue;
        }
        if (ui->stichwort_lineEdit->text() != "" && !arbeit.get_stichwortliste().contains(ui->stichwort_lineEdit->text())) {
            continue;
        }
        if (ui->betreuer_comboBox->currentData().isValid() && arbeit.get_betreuer()->get_id() != ui->betreuer_comboBox->currentData().toInt()) {
            continue;
        }
        if (ui->von_lineEdit->text() != "" && (arbeit.get_bis() != "" && arbeit.get_bis() < ui->von_lineEdit->text())) {
            continue;
        }
        if (ui->bis_lineEdit->text() != "" && arbeit.get_von() > ui->bis_lineEdit->text()) {
            continue;
        }
        if (ui->bearbeiter_lineEdit->text() != "" && !arbeit.get_bearbeiter().contains(ui->bearbeiter_lineEdit->text())) {
            continue;
        }

        // Create Item
        QListWidgetItem *current_item = new QListWidgetItem();

        // Adjust Item
        current_item->setText(arbeit.get_titel());
        current_item->setToolTip(QString::number(arbeit.get_id()));

        // Add Item
        ui->arbeiten_listWidget->addItem(current_item);

        // Add Signals/Slots
        QObject::connect(ui->arbeiten_listWidget, SIGNAL(itemActivated(QListWidgetItem*)), this, SLOT(arbeit_clicked(QListWidgetItem*)));
    }
}

void MainWindow::refresh_dozenten_list() {
    // Clear list
    ui->dozenten_listWidget->clear();

    // Get dozenten
    QList dozenten = db->get_dozentent();
    for (Dozent dozent : dozenten) {
        // Skip dozent wenn gefiltert
        if (ui->betreuer_comboBox->currentData().isValid() && ui->betreuer_comboBox->currentData().toInt() != dozent.get_id()) {
            continue;
        }

        // Create Item
        QListWidgetItem *current_item = new QListWidgetItem();

        // Adjust Item
        current_item->setText(dozent.get_name());
        current_item->setToolTip(dozent.get_email());

        // Add Item
        ui->dozenten_listWidget->addItem(current_item);

        // Add Signals/Slots
        QObject::connect(ui->dozenten_listWidget, SIGNAL(itemActivated(QListWidgetItem*)), this, SLOT(dozent_clicked(QListWidgetItem*)));
    }
}

void MainWindow::on_login_pushButton_clicked() {
    // Cancel if other dialog is open
    if (this->dialog_open) {
        return;
    }
    this->dialog_open = true;

    // Create dialog
    LoginDock *login_dialog = new LoginDock(this->db, this);

    // Add dialog to window
    ui->centralwidget->layout()->addWidget(login_dialog);

    // Adjust dialog
    login_dialog->setFloating(true);

    // Add Signals/Slots
    QObject::connect(login_dialog, SIGNAL(login_as_dozent(int,LoginDock*)), this, SLOT(login_as_dozent(int,LoginDock*)));
    QObject::connect(login_dialog, SIGNAL(login_as_admin(int,LoginDock*)), this, SLOT(login_as_admin(int,LoginDock*)));
    QObject::connect(login_dialog, SIGNAL(visibilityChanged(bool)), this, SLOT(dialog_closed(bool)));
}

void MainWindow::arbeit_clicked(QListWidgetItem *item) {
    // Cancel if other dialog is open
    if (this->dialog_open) {
        return;
    }
    this->dialog_open = true;

    // Create dialog
    Arbeit *arbeit = new Arbeit(item->toolTip().toInt());
    ArbeitDock *dialog;
    if (this->dozenten_session != nullptr) {
        dialog = new ArbeitDock(arbeit, this->dozenten_session->get_dozent());
    } else {
        dialog = new ArbeitDock(arbeit);
    }

    // Add dialog to window
    this->centralWidget()->layout()->addWidget(dialog);

    // Adjust dialog
    dialog->setFloating(true);

    // Add Signals/Slots
    QObject::connect(dialog, SIGNAL(visibilityChanged(bool)), this, SLOT(dialog_closed(bool)));
}

void MainWindow::dozent_clicked(QListWidgetItem *item) {
    // Cancel if other dialog is open
    if (this->dialog_open) {
        return;
    }
    this->dialog_open = true;

    // Create dialog
    Dozent *dozent = new Dozent(item->toolTip());
    AccountDock *dialog = new AccountDock(this->admin_session->get_admin(), dozent);

    // Add dialog to window
    this->centralWidget()->layout()->addWidget(dialog);

    // Adjust dialog
    dialog->setFloating(true);
    dialog->setWindowTitle(dozent->get_name());

    // Add Signals/Slots
    QObject::connect(dialog, SIGNAL(visibilityChanged(bool)), this, SLOT(dialog_closed(bool)));
}

void MainWindow::dialog_closed(bool value) {
    this->dialog_open = value;
    this->refresh_arbeiten_list();
    this->refresh_dozenten_list();
}

void MainWindow::login_as_dozent(int dozenten_id, LoginDock *origin) {
    // Create session
    this->dozenten_session = new DozentenSession(dozenten_id);

    // Remove Dialog
    origin->hide();
    delete origin;

    // Adjust visibility of UI Elements
    // Navbar - Upper
    ui->titel_lineEdit->show();
    ui->stichwort_lineEdit->show();
    ui->betreuer_comboBox->show();
    ui->von_lineEdit->show();
    ui->bis_lineEdit->show();
    ui->bearbeiter_lineEdit->show();
    // Navbar - Lower
    ui->dozentensuche_pushButton->hide();
    ui->projektsuche_pushButton->hide();
    ui->dozent_erstellen_pushButton->hide();
    ui->arbeit_erstellen_pushButton->show();
    ui->account_bearbeiten_pushButton->show();
    ui->logout_pushButton->show();
    ui->login_pushButton->hide();
    // Content
    ui->arbeiten_listWidget->show();
    ui->dozenten_listWidget->hide();

    // Adjust WindowTitle
    this->setWindowTitle("Arbeitsdatenbank - Projektsuche - Angemeldet als Dozent");

    // Add Filter
    int betreuer_index = ui->betreuer_comboBox->findData(dozenten_id);
    ui->betreuer_comboBox->setCurrentIndex(betreuer_index);

    // Check for required password change
    if (this->dozenten_session->get_dozent()->get_muss_passwort_andern()) {
        // Create dialog
        UpdatePasswortDock *update_passwort_dock = new UpdatePasswortDock(this->dozenten_session->get_dozent(), this);

        // Add dialog to window
        ui->centralwidget->layout()->addWidget(update_passwort_dock);

        // Adjust dialog
        update_passwort_dock->setFloating(true);
        update_passwort_dock->setFeatures(QDockWidget::DockWidgetFloatable);
    }
}

void MainWindow::login_as_admin(int admin_id, LoginDock *origin) {
    // Create session
    this->admin_session = new AdminSession(admin_id);

    // Remove Dialog
    origin->hide();
    delete origin;

    // Adjust visibility of UI Elements
    // Navbar - Upper
    ui->titel_lineEdit->hide();
    ui->stichwort_lineEdit->hide();
    ui->betreuer_comboBox->show();
    ui->von_lineEdit->hide();
    ui->bis_lineEdit->hide();
    ui->bearbeiter_lineEdit->hide();
    // Navbar - Lower
    ui->dozentensuche_pushButton->hide();
    ui->projektsuche_pushButton->show();
    ui->dozent_erstellen_pushButton->show();
    ui->arbeit_erstellen_pushButton->hide();
    ui->account_bearbeiten_pushButton->show();
    ui->logout_pushButton->show();
    ui->login_pushButton->hide();
    // Content
    ui->arbeiten_listWidget->hide();
    ui->dozenten_listWidget->show();

    // Adjust WindowTitle
    this->setWindowTitle("Arbeitsdatenbank - Dozentensuche - Angemeldet als Admin");
}

void MainWindow::on_dozentensuche_pushButton_clicked() {
    // Adjust visibility of UI Elements
    // Navbar - Upper
    ui->titel_lineEdit->hide();
    ui->stichwort_lineEdit->hide();
    ui->betreuer_comboBox->show();
    ui->von_lineEdit->hide();
    ui->bis_lineEdit->hide();
    ui->bearbeiter_lineEdit->hide();
    // Navbar - Lower
    ui->dozentensuche_pushButton->hide();
    ui->projektsuche_pushButton->show();
    ui->dozent_erstellen_pushButton->show();
    ui->arbeit_erstellen_pushButton->hide();
    ui->account_bearbeiten_pushButton->show();
    ui->logout_pushButton->show();
    ui->login_pushButton->hide();
    // Content
    ui->arbeiten_listWidget->hide();
    ui->dozenten_listWidget->show();

    // Adjust WindowTitle
    this->setWindowTitle("Arbeitsdatenbank - Dozentensuche - Angemeldet als Admin");
}

void MainWindow::on_projektsuche_pushButton_clicked() {
    // Adjust visibility of UI Elements
    // Navbar - Upper
    ui->titel_lineEdit->show();
    ui->stichwort_lineEdit->show();
    ui->betreuer_comboBox->show();
    ui->von_lineEdit->show();
    ui->bis_lineEdit->show();
    ui->bearbeiter_lineEdit->show();
    // Navbar - Lower
    ui->dozentensuche_pushButton->show();
    ui->projektsuche_pushButton->hide();
    ui->dozent_erstellen_pushButton->show();
    ui->arbeit_erstellen_pushButton->hide();
    ui->account_bearbeiten_pushButton->show();
    ui->logout_pushButton->show();
    ui->login_pushButton->hide();
    // Content
    ui->arbeiten_listWidget->show();
    ui->dozenten_listWidget->hide();

    // Adjust WindowTitle
    this->setWindowTitle("Arbeitsdatenbank - Projektsuche - Angemeldet als Admin");
}

void MainWindow::on_logout_pushButton_clicked() {
    // Adjust visibility of UI Elements
    // Navbar - Upper
    ui->titel_lineEdit->show();
    ui->stichwort_lineEdit->show();
    ui->betreuer_comboBox->show();
    ui->von_lineEdit->show();
    ui->bis_lineEdit->show();
    ui->bearbeiter_lineEdit->show();
    // Navbar - Lower
    ui->dozentensuche_pushButton->hide();
    ui->projektsuche_pushButton->hide();
    ui->dozent_erstellen_pushButton->hide();
    ui->arbeit_erstellen_pushButton->hide();
    ui->account_bearbeiten_pushButton->hide();
    ui->logout_pushButton->hide();
    ui->login_pushButton->show();
    // Content
    ui->arbeiten_listWidget->show();
    ui->dozenten_listWidget->hide();

    // Adjust WindowTitle
    this->setWindowTitle("Arbeitsdatenbank - Projektsuche");

    // Delete sessions
    if (this->dozenten_session != nullptr) {
        delete this->dozenten_session;
        this->dozenten_session = nullptr;
    }
    if (this->admin_session != nullptr) {
        delete this->admin_session;
        this->admin_session = nullptr;
    }
}

void MainWindow::on_account_bearbeiten_pushButton_clicked() {
    // Cancel if other dialog is open
    if (this->dialog_open) {
        return;
    }
    this->dialog_open = true;

    // Create dialog
    AccountDock *account_dock = nullptr;
    if (this->dozenten_session != nullptr) {
        account_dock = new AccountDock(this->dozenten_session->get_dozent());
    } else {
        account_dock = new AccountDock(this->admin_session->get_admin());
    }

    // Add dialog to window
    this->centralWidget()->layout()->addWidget(account_dock);

    // Adjust dialog
    account_dock->setFloating(true);
    account_dock->setWindowTitle("Dein Account");

    // Add Signals/Slots
    QObject::connect(account_dock, SIGNAL(visibilityChanged(bool)), this, SLOT(dialog_closed(bool)));
}

void MainWindow::on_dozent_erstellen_pushButton_clicked() {
    // Cancel if other dialog is open
    if (this->dialog_open) {
        return;
    }
    this->dialog_open = true;

    // Create dialog
    CreateDozentDock *dialog = new CreateDozentDock(this->db);

    // Add dialog to window
    this->centralWidget()->layout()->addWidget(dialog);

    // Adjust dialog
    dialog->setFloating(true);

    // Add Signals/Slots
    QObject::connect(dialog, SIGNAL(visibilityChanged(bool)), this, SLOT(dialog_closed(bool)));
}

void MainWindow::on_arbeit_erstellen_pushButton_clicked() {
    // Cancel if other dialog is open
    if (this->dialog_open) {
        return;
    }
    this->dialog_open = true;

    // Create dialog
    CreateArbeitDock *dialog = new CreateArbeitDock(this->db, this->dozenten_session->get_dozent());

    // Add dialog to window
    this->centralWidget()->layout()->addWidget(dialog);

    // Adjust dialog
    dialog->setFloating(true);

    // Add Signals/Slots
    QObject::connect(dialog, SIGNAL(visibilityChanged(bool)), this, SLOT(dialog_closed(bool)));
}

void MainWindow::on_clear_betreuer_pushButton_clicked() {
    // Unselect item
    ui->betreuer_comboBox->setCurrentIndex(-1);
}

void MainWindow::on_titel_lineEdit_textChanged(const QString &arg1) {
    // Apply filters when input occurs
    this->refresh_arbeiten_list();
}

void MainWindow::on_stichwort_lineEdit_textChanged(const QString &arg1) {
    // Apply filters when input occurs
    this->refresh_arbeiten_list();
}

void MainWindow::on_betreuer_comboBox_currentIndexChanged(int index) {
    // Apply filters when input occurs
    this->refresh_arbeiten_list();
    this->refresh_dozenten_list();
}

void MainWindow::on_von_lineEdit_textChanged(const QString &arg1) {
    // Apply filters when input occurs
    this->refresh_arbeiten_list();
}

void MainWindow::on_bis_lineEdit_textChanged(const QString &arg1) {
    // Apply filters when input occurs
    this->refresh_arbeiten_list();
}

void MainWindow::on_bearbeiter_lineEdit_textChanged(const QString &arg1) {
    // Apply filters when input occurs
    this->refresh_arbeiten_list();
}
