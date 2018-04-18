#include <QApplication>
#include <QIODevice>
#include <QFile>
#include <QFileInfo>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    /*file path*/
    QString path = "/home/reid/Documents/basic-vim-skills";


    /*init QFile object with path*/
    QFile file(path);


    /*condition sentence*/
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"fail to open the file";
        return -1;
    }
    else
    {
        while(!file.atEnd())  //QFile.atEnd() return true if it's not at EOF
        {
            qDebug()<<file.readLine();  //QFile.readLine()
        }
    }


    /*QFileInfo object init with QFile object.
      QFileInfo has mothods to show detailed info about QFile object.
      -------
      QFileInfo.isDir()
      */
    QFileInfo info(file);
    qDebug()<<"info.isDir() : "<<info.isDir();
    qDebug()<<"info.isexecutable() : "<<info.isExecutable();
    qDebug()<<"info.baseName() : "<<info.baseName();
    qDebug()<<"info.completeBaseName()"<<info.completeBaseName();
    qDebug()<<"info.suffix() : "<<info.suffix();
    qDebug()<<"info.completeSuffix() : "<<info.completeSuffix();

    return a.exec();
}
