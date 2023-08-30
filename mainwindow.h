#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>

QT_BEGIN_NAMESPACE
class QDialogButtonBox;
class QPushButton;
class QSqlTableModel;
QT_END_NAMESPACE

class DbView : public QWidget
{
    Q_OBJECT

public:
    explicit DbView(const QStringList &tableName, QWidget *parent = nullptr);

private slots:
    void submit();

private:
    QPushButton *submitButton;
    QPushButton *revertButton;
    QPushButton *quitButton;
    QDialogButtonBox *buttonBox;
    QSqlTableModel *model;
};

#endif
