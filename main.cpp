#include "mainwindow.h"

#include <QApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QStandardPaths>
#include <QDir>

#include "DBAccess.h"

int main(int argc, char *argv[]) {
    // Create Application
    QApplication a(argc, argv);

    // Default Directory
    QString app_data_path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "_GR8/";

    // Creates directory if it doesn't exist
    if (!QDir(app_data_path).exists()) {
        QDir().mkdir(app_data_path);
    }

    // Create Parser
    QCommandLineParser parser;
    // Add Parser options
    parser.addOption(QCommandLineOption("db_name", "Sets the name of the Database", "name", app_data_path + "db.sql"));
    // Parse Commandline Options
    parser.process(a);

    // Get path to DataBase
    QString db_name = parser.value("db_name");

    // Create DataBase
    DBAccess db(db_name);
    db.setup_database();

    // Reset DataBase to defaults
    if (parser.positionalArguments().contains("clean")) {
        db.reset_database();
    }

    // Add testvalues to DataBase
    if (parser.positionalArguments().contains("test")) {
        db.test_database();
    }

    // Create MainWindow
    MainWindow w(&db);
    w.show();
    return a.exec();
}
