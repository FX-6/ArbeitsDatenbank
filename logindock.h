#ifndef LOGINDOCK_H
#define LOGINDOCK_H

#include <QDockWidget>

#include "DBAccess.h"

namespace Ui {
class LoginDock;
}

class LoginDock : public QDockWidget
{
    Q_OBJECT

public:
    explicit LoginDock(DBAccess *db, QWidget *parent = nullptr);
    ~LoginDock();

private slots:
    void on_login_admin_pushButton_clicked();
    void on_login_dozent_pushButton_clicked();

signals:
    void login_as_admin(int admin_id, LoginDock *origin);
    void login_as_dozent(int dozenten_id, LoginDock *origin);

private:
    Ui::LoginDock *ui;
    DBAccess *db;
};

#endif // LOGINDOCK_H
