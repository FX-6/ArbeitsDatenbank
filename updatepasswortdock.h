#ifndef UPDATEPASSWORTDOCK_H
#define UPDATEPASSWORTDOCK_H

#include <QDockWidget>

#include "dozent.h"

namespace Ui {
class UpdatePasswortDock;
}

class UpdatePasswortDock : public QDockWidget
{
    Q_OBJECT

public:
    explicit UpdatePasswortDock(Dozent *dozent, QWidget *parent = nullptr);
    ~UpdatePasswortDock();

private slots:
    void on_andern_pushButton_clicked();

private:
    Ui::UpdatePasswortDock *ui;
    Dozent *dozent;
};

#endif // UPDATEPASSWORTDOCK_H
