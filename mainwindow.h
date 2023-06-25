#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>

#include "DBAccess.h"
#include "logindock.h"
#include "adminsession.h"
#include "dozentensession.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(DBAccess *db, QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void login_as_admin(int admin_id, LoginDock *origin);
    void login_as_dozent(int dozenten_id, LoginDock *origin);
    void arbeit_clicked(QListWidgetItem *item);
    void dozent_clicked(QListWidgetItem *item);
    void dialog_closed(bool value);

private slots:
    void on_login_pushButton_clicked();
    void on_dozentensuche_pushButton_clicked();
    void on_projektsuche_pushButton_clicked();
    void on_logout_pushButton_clicked();
    void on_account_bearbeiten_pushButton_clicked();
    void on_dozent_erstellen_pushButton_clicked();
    void on_arbeit_erstellen_pushButton_clicked();

    void on_clear_betreuer_pushButton_clicked();

    void on_titel_lineEdit_textChanged(const QString &arg1);

    void on_stichwort_lineEdit_textChanged(const QString &arg1);

    void on_betreuer_comboBox_currentIndexChanged(int index);

    void on_von_lineEdit_textChanged(const QString &arg1);

    void on_bis_lineEdit_textChanged(const QString &arg1);

    void on_bearbeiter_lineEdit_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    DBAccess *db;
    AdminSession *admin_session = nullptr;
    DozentenSession *dozenten_session = nullptr;
    bool dialog_open = false;
    void refresh_arbeiten_list();
    void refresh_dozenten_list();
};
#endif // MAINWINDOW_H
