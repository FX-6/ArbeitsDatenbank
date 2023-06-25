#ifndef CREATEARBEITDOCK_H
#define CREATEARBEITDOCK_H

#include <QDockWidget>

#include "DBAccess.h"
#include "dozent.h"

namespace Ui {
class CreateArbeitDock;
}

class CreateArbeitDock : public QDockWidget {
    Q_OBJECT

public:
    explicit CreateArbeitDock(DBAccess *db, Dozent *dozent, QWidget *parent = nullptr);
    ~CreateArbeitDock();

private slots:
    void on_create_pushButton_clicked();

private:
    Ui::CreateArbeitDock *ui;
    DBAccess *db;
    Dozent *dozent;
};

#endif // CREATEARBEITDOCK_H
