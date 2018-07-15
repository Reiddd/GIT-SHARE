#ifndef CHATDIALOG_H
#define CHATDIALOG_H

#include <QDialog>
#include "ui_chatdialog.h"
#include "client.h"

class ChatDialog : public  QDialog,
                   private Ui::ChatDialog /* QLineEdit*     lineEdit   : for accepting user input
                                             QTextEdit*     textEdit   : for showing nick name and message
                                             QLabel*        label      : buddy with lineEdit with text "message: " on it
                                             QListWidget*   listWidget : for showing all users currently in the group     */
{
    Q_OBJECT

public:
    ChatDialog(QWidget *parent = 0);
    ~ChatDialog();

public slots:
    void appendMessage(const QString& from, const QString& message);  // mainly use QTextCursor to append messages to the end of textEdit.

private slots:
    void returnPressed();                                             /* user presses return
                                                                         call ChatDialog::appendMessage || client.sendMessage || lineEdit->clear */
    void newParticipant (const QString& nick);                        /* new participant joins the group
                                                                         call textEdit->append || listWidget->addItem */
    void participantLeft(const QString& nick);
    void showInformation();

private:
    Client           client;
    QString          myNickName;
    QTextTableFormat tableFormat;
};

#endif // CHATDIALOG_H
