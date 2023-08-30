#include "conn.h"

bool Conn::createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName(query.hostName);
    db.setPort(query.port);
    db.setDatabaseName(query.dbName);
    db.setUserName(query.userName);
    db.setPassword(query.password);
    if (!db.open()) {
        QMessageBox::critical(nullptr, QObject::tr("Cannot open database"),
            QObject::tr("Unable to establish a database connection.\n"
                        "This example needs PSQL support. Please read "
                        "the Qt SQL driver documentation for information how "
                        "to build it.\n\n"
                        "Click Cancel to exit."), QMessageBox::Cancel);
        return false;
    }
    connDb = db;
    return true;
}

CommandLineParseResult Conn::parseCommandLine(QCommandLineParser &parser, ConnQuery *query, QString *errorMessage)
{
    parser.setSingleDashWordOptionMode(QCommandLineParser::ParseAsLongOptions);
    const QCommandLineOption hostNameOption("host", "The hostname server to use.", "host");
    parser.addOption(hostNameOption);
    const QCommandLineOption portOption("port", "The server port.", "port");
    parser.addOption(portOption);
    const QCommandLineOption dbOption("db", "The database name.", "db name");
    parser.addOption(dbOption);
    const QCommandLineOption userOption("u", "The username.", "user");
    parser.addOption(userOption);
    const QCommandLineOption passwordOption("password", "The password.", "password");
    parser.addOption(passwordOption);
    const QCommandLineOption helpOption = parser.addHelpOption();
    const QCommandLineOption versionOption = parser.addVersionOption();

    if (!parser.parse(QCoreApplication::arguments())) {
        *errorMessage = parser.errorText();
        return CommandLineError;
    }

    if (parser.isSet(versionOption))
        return CommandLineVersionRequested;

    if (parser.isSet(helpOption))
        return CommandLineHelpRequested;

    if (parser.isSet(hostNameOption)) {
        const QString host = parser.value(hostNameOption);
        query->hostName = host;
        if (QHostAddress(host).isNull() || QHostAddress(host).protocol() == QAbstractSocket::UnknownNetworkLayerProtocol) {
            *errorMessage = "Bad host: " + host;
            return CommandLineError;
        }
    }

    if (parser.isSet(portOption)) {
        const QString portString = parser.value(portOption);
        query->port = portString.toInt();
        if (query->port < 0) {
            *errorMessage = "Bad port: " + portString;
            return CommandLineError;
        }
    }

    if (parser.isSet(dbOption)) {
        const QString db = parser.value(dbOption);
        query->dbName = db;
        if (db.isNull() || db.isEmpty()) {
            *errorMessage = "Bad db name: " + db;
            return CommandLineError;
        }
    }

    if (parser.isSet(userOption)) {
        const QString user = parser.value(userOption);
        query->userName = user;
        if (user.isNull() || user.isEmpty()) {
            *errorMessage = "Bad username: " + user;
            return CommandLineError;
        }
    }

    if (parser.isSet(passwordOption)) {
        const QString password = parser.value(passwordOption);
        query->password = password;
        if (password.isNull() || password.isEmpty()) {
            *errorMessage = "Bad password: " + password;
            return CommandLineError;
        }
    }

    return CommandLineOk;
}
