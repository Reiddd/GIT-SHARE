#include "tableeditor.h"
#include <QSqlError>

TableEditor::TableEditor(const QString& tableName, QWidget *parent)
    : QWidget(parent),
      model       (new QSqlTableModel(this)),
      submitButton(new QPushButton("Submit")),
      revertButton(new QPushButton("&Revert")),
      quitButton  (new QPushButton("quit")),
      buttonBox   (new QDialogButtonBox(Qt::Vertical))
{
/* ------- model ------- */

    model->setTable(tableName);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();

/* ------- header ------- */

    model->setHeaderData(0, Qt::Horizontal, tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, tr("First Name"));
    model->setHeaderData(2, Qt::Horizontal, tr("Last Name"));

/* ------- view ------- */

    QTableView* view = new QTableView;
    view->setModel(model);
    view->resizeColumnsToContents();

/* ------ buttons ------- */

    submitButton->setDefault(true);

    buttonBox->addButton(submitButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(revertButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(quitButton  , QDialogButtonBox::RejectRole);

/* ------- layout ------- */

    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(view);
    mainLayout->addWidget(buttonBox);

    setLayout(mainLayout);
    setWindowTitle("Cached Table");

/* ------- signal to slot ------- */

    connect(submitButton, &QPushButton::clicked,
            this        , &TableEditor::submit);

    connect(revertButton, &QPushButton::clicked,
            model       , &QSqlTableModel::revertAll);

    connect(quitButton  , &QPushButton::clicked,
            this        , &TableEditor::close);
}


TableEditor::~TableEditor()
{

}


/* 1. begin the transaction
   2. try to submit
          I. if submit failed, rollback the transaction
          II. if submit successfully, commit the transaction
   3. both rollback and submit close the transaction            */
void TableEditor::submit()
{
    model->database().transaction();    // bool QSqlDatabase::transaction() begins the tranction and returns true on success
    if(model->submitAll())              // bool QAbstractItemModel::submitAll()
        model->database().commit();     // bool QSqlDatabase::commit()  requires the transaction is opened
    else{
        model->database().rollback();   // bool QSqlDatabase::rollback()
        QMessageBox::warning(this, tr("Cached Table"), tr("The database reported an error:\n%1").arg(model->lastError().text()));
    }
}
