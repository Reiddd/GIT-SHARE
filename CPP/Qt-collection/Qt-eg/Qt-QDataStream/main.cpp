#include <QApplication>
#include <QDataStream>
#include <QFile>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /*create a QFile object and open it*/
    QFile file("/home/reid/Documents/Qt-collection/Qt-eg/QDataStream/file-example");
    file.open(QIODevice::WriteOnly);

    /*create a QDataStream*/
    QDataStream out(&file);

    /*save QT type data into file, so it could be read correctly on different platform.*/
    out<<QString("this is an example of 'QString' in QDataStream\n");
    out<<QString("this is an example of 'qint32' in 'QDataStream' : ")<<(qint32)42; //qint8, qint16, qint32, qint64

    /*if you want the change in file be saved, the file should be closed or flushed*/
    file.flush();

    /*set the pointer pointing to the head of stream, because addition makes it point to the end of stream*/
    out.device()->seek(0);

    QString str;
    out>>str;
    qDebug()<<str;

    /*always close the file*/
    file.close();

    return a.exec();
}
