#include "searchbox.h"
#include <QDesktopServices>
#include <QUrl>

const QString bingSuggestUrl = QStringLiteral("http://cn.bing.com/search?q=%1");

SearchBox::SearchBox(QWidget *parent)
    : QLineEdit(parent)
{
    completer = new BingSuggest(this);
    connect(this, SIGNAL(returnPressed()),
            this, SLOT(doSearch() ));
    setWindowTitle("Search with Bing");
    adjustSize();
    resize(400, height());
    setFocus();
}


SearchBox::~SearchBox()
{

}


void SearchBox::doSearch()
{
    completer->preventSuggest();
    QString url = bingSuggestUrl.arg(text());
    QDesktopServices::openUrl(url);
}
