#include "mainwindow.h"

#include <QApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QStandardPaths>
#include <QDir>
#include "DBAccess.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QString app_data_path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "_GR8/";
    if (!QDir(app_data_path).exists()) {
        QDir().mkdir(app_data_path);
    }

    QCommandLineParser parser;
    parser.addOption(QCommandLineOption("db_name", "Sets the name of the Database", "name", app_data_path + "db.sql"));
    parser.process(a);

    QString db_name = parser.value("db_name");
    DBAccess db(db_name);
    db.setup_database();

    if (parser.positionalArguments().contains("clean")) {
        db.reset_database();
    }

    if (parser.positionalArguments().contains("test")) {
        db.test_database();
    }

    MainWindow w(&db);
    w.show();
    return a.exec();
}
