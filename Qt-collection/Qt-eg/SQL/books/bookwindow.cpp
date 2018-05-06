#include "bookwindow.h"
#include "bookdelegate.h"
#include "initdb.h"

BookWindow::BookWindow(QWidget *parent)
    : QMainWindow(parent)
{
/* ------- setup ui ------- */

    ui.setupUi(this);

/* ------- check available drivers ------- */

    if(!QSqlDatabase::drivers().contains("QSQLITE"))                                                    // QStringList QSqlDatabase::drivers() returns all available drivers
        QMessageBox::critical(this, "Unable to load database", "This demo needs the SQLITE driver.");

/* ------- initialize database ------- */

    QSqlError err = initDb();
    if(err.type() != QSqlError::NoError){
        showError(err);
        return;
    }

/* ------- create data model ------- */

    model = new QSqlRelationalTableModel(ui.bookTable);                                                 // ui.bookTable -> QTableView
                                                                                                        // QSqlRelationalTableModel(QTableView )
    /* QSqlTableModel::OnFieldChange  : all changes in the model will be applied to the database immediately.
       QSqlTableModel::OnRowChange    : changes in the model will be applied to the database when user chooses different row.
       QSqlTableModel::OnManualSubmit : changes will only be applied to the database when submitAll() or revertAll() is called. */
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);                                             // QSqlTableModel::EditStrategy QSqlRelationalTableModel::setEditStrategy(QSqlTableModel::EditStrategy ) returns current edit strategy
    model->setTable("books");                                                                           // void QSqlTableModel::setTable(const QString& )

/* ------- field index ------- */

    authorIdx = model->fieldIndex("author");
    genreIdx  = model->fieldIndex("genre");

/* ------- relation ------- */

    model->setRelation(authorIdx, QSqlRelation("authors", "id", "name"));                               // QSqlRelation(QString tableName, QString foreignKey, QString displayField)
    model->setRelation(genreIdx , QSqlRelation("genres" , "id", "name"));

/* ------- header ------- */

    model->setHeaderData(authorIdx                  , Qt::Horizontal, "Author Name");                   // bool QAbstractItemModel::setHeaderData(int section, Qt::Orientation, const QVariant& value, int role = Qt::EditRole)
    model->setHeaderData(genreIdx                   , Qt::Horizontal, "Genre");
    model->setHeaderData(model->fieldIndex("title") , Qt::Horizontal, tr("Title"));
    model->setHeaderData(model->fieldIndex("year")  , Qt::Horizontal, tr("Year"));
    model->setHeaderData(model->fieldIndex("rating"), Qt::Horizontal, tr("Rating"));

/* ------- populate the model ------- */

    if(!model->select()){                                                                               // bool QSqlTableModel::select()
        showError(model->lastError());                                                                  // QSqlError QSqlQueryModel::lastError()
        return;
    }

/* ------- mapping model to gui ------- */

    ui.bookTable->setModel(model);                                                                      // void QTableView::setModel(QAbstractItemModel* )
    ui.bookTable->setItemDelegate(new BookDelegate(ui.bookTable));                                   // void QAbstractItemView::setItemDelegate(QAbstractItemDelegate* )
    ui.bookTable->setColumnHidden(model->fieldIndex("id"), true);                                       // void QTableView::setColumnHidden(int collumn, bool hide)
    /* QAbstractItemView::SingleSelection     : when user selects an item, any selected items become unselected.
       QAbstractItemView::ContiguousSelection : based on SingleSelection, when clicking on an item with shift pressed, all items between the selected and the clicked will be selected or unselected depending on whether clicking select or unselect the item.
       QAbstractItemView::MultiSelection      :
       QabstractItemView::NoSelection         :                                                                                                                                                                                                                 */
    ui.bookTable->setSelectionMode(QAbstractItemView::SingleSelection);                                 // void QAbstractItemView::setSelectionMode(QAbstractItemView::SelectionMode )
    ui.bookTable->setCurrentIndex(model->index(0, 0));

    ui.authorEdit->setModel(model->relationModel(authorIdx));                                           // QSqlTableModel* QSqlTableModel::relationModel(int foreignKeyIndex) returns the model which the foreignKey is related to.
    ui.authorEdit->setModelColumn(model->relationModel(authorIdx)->fieldIndex("name"));                 // void QComboBox::setModel(QAbstractItemModel* )
                                                                                                        // void QComboBox::setModelColumn(int index) , modelColumn : the displayed column in the model

    ui.genreEdit->setModel(model->relationModel(genreIdx));
    ui.genreEdit->setModelColumn(model->relationModel(genreIdx)->fieldIndex("name"));

    QDataWidgetMapper* mapper = new QDataWidgetMapper(this);
    mapper->setModel(model);
    mapper->setItemDelegate(new BookDelegate(this));
    mapper->addMapping(ui.titleEdit , model->fieldIndex("title"));
    mapper->addMapping(ui.yearEdit  , model->fieldIndex("year"));
    mapper->addMapping(ui.authorEdit, authorIdx);
    mapper->addMapping(ui.genreEdit , genreIdx);
    mapper->addMapping(ui.ratingEdit, model->fieldIndex("rating"));

/* ------- signal to slot ------- */

    connect(ui.bookTable->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)),        // QItemSelectionModel* QAbstractItemView::selectionModel()
            mapper                        , SLOT(setCurrentModelIndex(QModelIndex)));
}


BookWindow::~BookWindow()
{

}


void BookWindow::showError(const QSqlError& err)
{
    QMessageBox::critical(this, "Unable to initialize database", "error initializing the database: \n" + err.text());   // QString QSqlError::text()
}
