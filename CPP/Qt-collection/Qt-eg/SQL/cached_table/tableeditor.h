#ifndef TABLEEDITOR_H
#define TABLEEDITOR_H

#include <QtWidgets>
#include <QtSql/QSqlTableModel>

class TableEditor : public QWidget
{
    Q_OBJECT

public:
    explicit TableEditor(const QString& tableName, QWidget *parent = 0);
    ~TableEditor();

private slots:
    void submit();

private:
    QPushButton*      submitButton;
    QPushButton*      revertButton;
    QPushButton*      quitButton;
    QDialogButtonBox* buttonBox;
    QSqlTableModel*   model;
};

#endif // TABLEEDITOR_H
