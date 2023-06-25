#ifndef ARBEITDOCK_H
#define ARBEITDOCK_H

#include <QDockWidget>

#include "arbeit.h"
#include "dozent.h"

namespace Ui {
class ArbeitDock;
}

class ArbeitDock : public QDockWidget {
    Q_OBJECT

public:
    explicit ArbeitDock(Arbeit *arbeit, QWidget *parent = nullptr);
    explicit ArbeitDock(Arbeit *arbeit, Dozent *dozent, QWidget *parent = nullptr);
    ~ArbeitDock();

private slots:
    void on_loschen_pushButton_clicked();

    void on_speichern_pushButton_clicked();

private:
    Ui::ArbeitDock *ui;
    Arbeit *arbeit;
    Dozent *dozent = nullptr;
    int og_typ;
    QString og_titel;
    QString og_bearbeiter;
    int og_status;
    QString og_studiengang;
    QString og_stichwortliste;
    QString og_erlauterung;
    QString og_von;
    QString og_bis;
    QString og_firma;
    QString og_semester;
};

#endif // ARBEITDOCK_H
