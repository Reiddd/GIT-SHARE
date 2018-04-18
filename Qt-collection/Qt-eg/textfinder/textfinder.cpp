#include "textfinder.h"
#include "ui_textfinder.h"

#include <QFile>
#include <QTextStream>

textFinder::textFinder(QWidget *parent) :
    QWidget(parent)
{
    ui.setupUi(this);
    loadTextFile();
}


void textFinder::on_findButton_clicked()
{
    QString searchString = ui.lineEdit->text();
    ui.textEdit->find(searchString,QTextDocument::FindWholeWords);
}

void textFinder::loadTextFile()
{
    QFile inputFile("/home/reid/Documents/Qt-collection/Qt-eg/textfinder/basic-vim-skills");
    inputFile.open(QIODevice::ReadOnly);

    QTextStream in(&inputFile);
    QString line = in.readAll();

    inputFile.close();

    ui.textEdit->setPlainText(line);
    QTextCursor cursor = ui.textEdit->textCursor();
    cursor.movePosition(QTextCursor::Start,QTextCursor::MoveAnchor,1);
}
