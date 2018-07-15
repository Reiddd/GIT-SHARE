#include "chatdialog.h"
#include <QtWidgets>

ChatDialog::ChatDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);

    /* Qt::FocusPolicy
           Qt::TabFocus    : the widget starts to accept focus by tabbing.
           Qt::ClickFocus  : the widget starts to accept focus by clicking.
           Qt::StrongFocus : Qt::TabFocus    + Qt::ClickFocus.
           Qt::WheelFocus  : Qt::StrongFocus + wheelFocus.
           Qt::NoFocus     : the widget can't be focus.                      */
    lineEdit->setFocusPolicy(Qt::StrongFocus);
    textEdit->setFocusPolicy(Qt::NoFocus);
    textEdit->setReadOnly(true);
    listWidget->setFocusPolicy(Qt::NoFocus);

    connect(lineEdit, SIGNAL(returnPressed()),
            this    , SLOT(returnPressed()));

 /* connect(lineEdit, SIGNAL(returnPressed()),
            this    , SLOT(returnPressed()));  */

    connect(&client , SIGNAL(newMessage(QString, QString)),
            this    , SLOT(appendMessage(QString, QString)));

    connect(&client , SIGNAL(newParticipant(QString)),
            this    , SLOT(newParticipant(QString)));

    connect(&client , SIGNAL(participantLeft(QString)),
            this    , SLOT(participantLeft(QString)));

    myNickName = client.nickName();
    newParticipant(myNickName);
    tableFormat.setBorder(0);
    QTimer::singleShot(10 * 1000, this, SLOT(showInformation()));
}


ChatDialog::~ChatDialog()
{

}


void ChatDialog::appendMessage(const QString& from, const QString& message)
{
    if(from.isEmpty() || message.isEmpty())
        return;

    QTextCursor cursor(textEdit->textCursor());
    /* QTextCursor::Start         || QTextCursor::End
       QTextCursor::StartOfLine   || QTextCursor::EndOfLine
       QTextCursor::StartOfWord   || QTextCursor::EndOfWord
       QTextCursor::StartOfBlock  || QTextCursor::EndOfBlock

       QTextCursor::PreviousWord  || QTextCursor::NextWord
       QTextCursor::PreviousBlock || QTextCursor::NextBlock
       QTextCursor::PreviousRow   || QTextCursor::NextRow
       QTextCursor::PreviousCell  || QTextCursor::NextCell

       QTextCursor::Left          || QTextCursor::Right
       QTextCursor::Up            || QTextCursor::Down       */
    cursor.movePosition(QTextCursor::End);                                    /* bool           QTextCursor::movePosition(QTextCursor::MoveOperation operation,
                                                                                                                       QTextCursor::MoveMode      mode        = QTextCursor::MoveAnchor,
                                                                                                                       int                        repeatTimes = 1)                       */
    QTextTable* table = cursor.insertTable(1, 2, tableFormat);                // QTextTable*    QTextCursor::insertTable(int row, int col, const QTextTableFormat& format)
    table->cellAt(0, 0).firstCursorPosition().insertText('<' + from + "> ");  /* QTextTableCell QTextTable::cellAt(int row, int col)
                                                                                 QTextCursor    QTextTableCell::firstCursorPosition()
                                                                                 void           QTextCursor::insertText(const QString& text)
                                                                                 void           QTextCursor::insertText(const QString& text, const QTextCharFormat& format) */
    table->cellAt(0, 1).firstCursorPosition().insertText(message);

    QScrollBar* bar = textEdit->verticalScrollBar();
    bar->setValue(bar->maximum());
}


void ChatDialog::returnPressed()
{
    QString text = lineEdit->text();

    if(text.isEmpty())
        return;

    if(text.startsWith(QChar('/'))){
        QColor color = textEdit->textColor();
        textEdit->setTextColor(Qt::red);
        textEdit->append(tr("! Unknown command: %1").arg(text.left(text.indexOf(' '))));  // void QTextEdit::append(const QString& content) appends a new paragraph with content
        textEdit->setTextColor(color);
    }
    else{
        client.sendMessage(text);
        appendMessage(myNickName, text);
    }

    lineEdit->clear();
}


void ChatDialog::newParticipant(const QString& nick)
{
    if(nick.isEmpty())
        return;

    QColor color = textEdit->textColor();
    textEdit->setTextColor(Qt::gray);
    textEdit->append(tr("%1 has joined.").arg(nick));
    textEdit->setTextColor(color);
    listWidget->addItem(nick);
}


void ChatDialog::participantLeft(const QString& nick)
{
    if(nick.isEmpty())
        return;

    /* Qt::MatchExactly       : QVariant based, case sensitive
       Qt::MatchFixedString   : QString  based, case insensitive
       Qt::MatchCaseSensitive :
       Qt::MatchContains      : the result contains the search term
       Qt::MatchStartsWith    :
       Qt::MatchEndsWith      :
       Qt::MatchRegExp        :
       Qt::MatchWildCard      :*/
    QList<QListWidgetItem*> items = listWidget->findItems(nick, Qt::MatchExactly);  // QList<QListWidgetItem*> QListWidget::findItems(const QString& text, Qt::MatchFlags flag)

    if(!items.empty()){
        delete items.at(0);
        QColor color = textEdit->textColor();
        textEdit->setTextColor(Qt::gray);
        textEdit->append(tr("* %1 has left").arg(nick));
        textEdit->setTextColor(color);
    }
}


void ChatDialog::showInformation()
{
    if(listWidget->count() == 1){
        QMessageBox::information(this,
                                 tr("Chat"),
                                 tr("Only one user."
                                    "try launching some new instances."));
    }
}
