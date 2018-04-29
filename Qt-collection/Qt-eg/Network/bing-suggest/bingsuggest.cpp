#include "bingsuggest.h"
#include <QtNetwork/QNetworkReply>
#include <QTreeWidget>

const QString bingSuggestUrl(QStringLiteral("http://cn.bing.com/search?q=%1"));

BingSuggest::BingSuggest(QLineEdit *parent)
    : QObject(parent),
      editor (parent),
      popup  (new QTreeWidget)
{
/* ------- gui ------- */

    popup->setWindowFlags(Qt::Popup);
    popup->setFocusPolicy(Qt::NoFocus);
    popup->setFocusProxy(parent);
    popup->setMouseTracking(true);
    popup->setColumnCount(1);
    popup->setUniformRowHeights(true);
    popup->setRootIsDecorated(false);
    popup->setEditTriggers(QTreeWidget::NoEditTriggers);
    popup->setSelectionBehavior(QTreeWidget::SelectRows);
    popup->setFrameStyle(QFrame::Box | QFrame::Plain);
    popup->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    popup->header()->hide();
    popup->installEventFilter(this);

/* ------- timer ------- */

    timer.setSingleShot(true);
    timer.setInterval(500);

/* ------- signal to slot ------- */

    connect(popup          , SIGNAL(itemClicked(QTreeWidgetItem*, int)),
            this           , SLOT(doneCompletion()));

    connect(&timer         , SIGNAL(timeout()),
            this           , SLOT(autoSuggest()));

    connect(&networkManager, SIGNAL(finished(QNetworkReply*)),
            this           , SLOT(handleNetworkData(QNetworkReply*)));
}


BingSuggest::~BingSuggest()
{
    delete popup;
}


bool BingSuggest::eventFilter(QObject* object, QEvent* event)
{
    if(object != popup)
        return false;

    if(event->type() == QEvent::MouseButtonPress){
        popup->hide();
        editor->setFocus();
        return true;
    }

    if(event->type() == QEvent::KeyPress){
        bool consumed = false;
        int key = static_cast<QKeyEvent*>(event)->key();  // static_cast for baseClass <=> childClass
        switch(key){
        case Qt::Key_Enter:
        case Qt::Key_Return:
            doneCompletion();
            consumed = true;
            break;
        case Qt::Key_Escape:
            editor->setFocus();
            popup->hide();
            consumed = true;
            break;
        case Qt::Key_Up:
        case Qt::Key_Down:
        case Qt::Key_Home:
        case Qt::Key_End:
        case Qt::Key_PageUp:
        case Qt::Key_PageDown:
            break;
        default:
            editor->setFocus();
            editor->event(event);                          /* bool QObject::event(QEvent* )

                                                                  let the object process the event and return true on success

                                                                  always pass unhandled event to parent object or some others.
                                                           */
            popup->hide();
            break;
        }
        return consumed;
    }

    return false;
}


void BingSuggest::showCompletion(const QVector<QString>& choices)
{
    if(choices.isEmpty())
        return;

    const QPalette& pal   = editor->palette();
    QColor          color = pal.color(QPalette::Disabled, QPalette::WindowText);

    popup->setUpdatesEnabled(false);
    popup->clear();

    for(const QString& choice : choices){
        QTreeWidgetItem* item = new QTreeWidgetItem(popup);
        item->setText(0, choice);
        item->setTextColor(0, color);
    }

    popup->setCurrentItem(popup->topLevelItem(0));
    popup->resizeColumnToContents(0);
    popup->setUpdatesEnabled(true);
    popup->move(editor->mapToGlobal(QPoint(0, editor->height() )));
    popup->setFocus();
    popup->show();
}


void BingSuggest::doneCompletion()
{
    timer.stop();
    popup->hide();
    editor->setFocus();
    QTreeWidgetItem* item = popup->currentItem();
    if(item){
        editor->setText(item->text(0));
        QMetaObject::invokeMethod(editor, "returnPressed");
    }
}


void BingSuggest::autoSuggest()
{
    QString str = editor->text();
    QString url = bingSuggestUrl.arg(str);
    networkManager.get(QNetworkRequest(url));  /* QNetworkReply* QNetworkAccessManager::get(QNetworkRequest& request)

                                                  QNetworkReply object will send a readyRead signal when finished :
                                                      QNetworkReply*        reply;
                                                      QNetworkAccessManager manager;
                                                      connect(reply     , QNetworkReply::readyRead,
                                                              yourObject, yourSlot);
                                                      reply = manager.get(request);

                                                  QNetworkAccessManager  object will send a finished signal when finished :
                                                      QNetworkAccessManager manager;
                                                      connect(&manager  , QNetworkAccessManager::finished,
                                                              yourObject, yourSlot);
                                                      manager.get(request); */
}


void BingSuggest::preventSuggest()
{
    timer.stop();
}


void BingSuggest::handleNetworkData(QNetworkReply* reply)
{
    QUrl url = reply->url();                                          // QUrl QNetworkReply::url()
    if(reply->error() == QNetworkReply::NoError){
        QVector<QString> choices;

        QByteArray response(reply->readAll());
        QXmlStreamReader xml(response);
        while(!xml.atEnd()){
            xml.readNext();
            if(xml.tokenType() == QXmlStreamReader::StartElement)
                if(xml.name()  == "suggestion"){
                    QStringRef str = xml.attributes().value("data");
                    choices<<str.toString();
                }
        }
        showCompletion(choices);
    }
    reply->deleteLater();
}
