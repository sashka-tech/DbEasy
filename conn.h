#ifndef CONN_H
#define CONN_H

#include <QObject>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QHostAddress>

enum CommandLineParseResult
{
    CommandLineOk,
    CommandLineError,
    CommandLineVersionRequested,
    CommandLineHelpRequested
};

struct ConnQuery
{
    ConnQuery() {}
    QString hostName;
    int port;
    QString dbName;
    QString userName;
    QString password;
};

class Conn : public QObject
{
    Q_OBJECT
public:
    explicit Conn(QObject *parent = nullptr) : QObject(parent){};

    void setQuery(const ConnQuery &q) { query = q; }
    QSqlDatabase getDb() { return connDb; }
    bool createConnection();
    static CommandLineParseResult parseCommandLine(QCommandLineParser &parser, ConnQuery *query, QString *errorMessage);
private:
    ConnQuery query;
    QSqlDatabase connDb;
};

#endif // CONN_H
