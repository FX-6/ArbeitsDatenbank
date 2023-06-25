#ifndef CREATEDOZENTDOCK_H
#define CREATEDOZENTDOCK_H

#include <QDockWidget>

#include "DBAccess.h"

namespace Ui {
class CreateDozentDock;
}

class CreateDozentDock : public QDockWidget {
    Q_OBJECT

public:
    explicit CreateDozentDock(DBAccess *db, QWidget *parent = nullptr);
    ~CreateDozentDock();

private slots:
    void on_erstellen_pushButton_clicked();

private:
    Ui::CreateDozentDock *ui;
    DBAccess *db;
};

#endif // CREATEDOZENTDOCK_H
