#ifndef ACCOUNTDOCK_H
#define ACCOUNTDOCK_H

#include <QDockWidget>

#include "dozent.h"
#include "admin.h"

namespace Ui {
class AccountDock;
}

class AccountDock : public QDockWidget {
    Q_OBJECT

public:
    explicit AccountDock(Dozent *dozent, QWidget *parent = nullptr);
    explicit AccountDock(Admin *admin, Dozent *dozent = nullptr, QWidget *parent = nullptr);
    ~AccountDock();

private slots:
    void on_email_lineEdit_textEdited(const QString &arg1);
    void on_passwort_andern_pushButton_clicked();
    void on_loschen_pushButton_clicked();
    void on_bestatigen_pushButton_clicked();

private:
    Ui::AccountDock *ui;
    Dozent *dozent = nullptr;
    Admin *admin = nullptr;
    QString og_nachname;
    QString og_vorname;
    QString og_email;
};

#endif // ACCOUNTDOCK_H
