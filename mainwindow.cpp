#include <QtWidgets>
#include <QtSql>

#include "mainwindow.h"

DbView::DbView(const QStringList &tableNames, QWidget *parent)
    : QWidget(parent)
{
    this->setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    this->setFixedSize(sizeHint());
    QLabel* dbName = new QLabel;

    QComboBox *tablesBox = new QComboBox;
    tablesBox->addItems(tableNames);

    model = new QSqlTableModel(this);
    model->setTable(tablesBox->currentText());
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();

    dbName->setText("Database name: " + model->database().databaseName());

    QTableView *view = new QTableView;
    view->setModel(model);
    view->resizeColumnsToContents();
    view->setFixedSize(view->sizeHint());

    submitButton = new QPushButton(tr("Submit"), this);
    submitButton->setDefault(true);
    revertButton = new QPushButton(tr("&Revert"), this);
    quitButton = new QPushButton(tr("Quit"), this);

    buttonBox = new QDialogButtonBox(Qt::Horizontal);
    buttonBox->addButton(submitButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(revertButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(quitButton, QDialogButtonBox::RejectRole);

    connect(tablesBox, &QComboBox::currentTextChanged, this, [this, tablesBox]()-> void {
        model->setTable(tablesBox->currentText());
        model->setEditStrategy(QSqlTableModel::OnManualSubmit);
        model->select();
    });
    connect(submitButton, &QPushButton::clicked, this, &DbView::submit);
    connect(revertButton, &QPushButton::clicked,  model, &QSqlTableModel::revertAll);
    connect(quitButton, &QPushButton::clicked, this, &DbView::close);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setSizeConstraint(QLayout::SizeConstraint::SetDefaultConstraint);
    mainLayout->addWidget(dbName);
    mainLayout->addWidget(tablesBox);
    mainLayout->addWidget(view);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);

    setWindowTitle(tr("DbEasy"));

}

void DbView::submit()
{
    model->database().transaction();
    if (model->submitAll()) {
        model->database().commit();
    } else {
        model->database().rollback();
        QMessageBox::warning(this, tr("DbEasy"),
                             tr("The database reported an error: %1")
                             .arg(model->lastError().text()));
    }
}
