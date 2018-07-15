#ifndef SEARCHBOX_H
#define SEARCHBOX_H

#include <QLineEdit>
#include "bingsuggest.h"

class SearchBox : public QLineEdit
{
    Q_OBJECT

public:
    SearchBox(QWidget *parent = 0);
    ~SearchBox();

protected slots:
    void doSearch();

private:
    BingSuggest* completer = nullptr;
};

#endif // SEARCHBOX_H
