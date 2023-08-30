#include <QApplication>

#include "conn.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QCoreApplication::setApplicationVersion(QT_VERSION_STR);
    QCoreApplication::setApplicationName(QCoreApplication::translate("DbEasy", "DB"));
    QCommandLineParser parser;
    parser.setApplicationDescription(QCoreApplication::translate("DbEasy", "Test the database connection and edit the data in the tables if you like."));
    ConnQuery query;
    QString errorMessage;
    switch (Conn::parseCommandLine(parser, &query, &errorMessage)) {
    case CommandLineOk:
        break;
    case CommandLineError:
        fputs(qPrintable(errorMessage), stderr);
        fputs("\n\n", stderr);
        fputs(qPrintable(parser.helpText()), stderr);
        return 1;
    case CommandLineVersionRequested:
        printf("%s %s\n", qPrintable(QCoreApplication::applicationName()),
               qPrintable(QCoreApplication::applicationVersion()));
        return 0;
    case CommandLineHelpRequested:
        parser.showHelp();
        Q_UNREACHABLE();
    }

    Conn conn;
    conn.setQuery(query);
    if (!conn.createConnection()){
        return 1;
    }

    DbView editor(conn.getDb().tables());
    editor.show();
    return app.exec();
}
