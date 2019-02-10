#ifndef DATAPROVIDER_H
#define DATAPROVIDER_H
#include <QtNetwork>
#include <QDebug>
#include <QList>
class dataProvider
{
public:
    dataProvider();
    QVariant  request(QString requestString);
    QVariant  sender(QByteArray rawdata);

};

#endif // DATAPROVIDER_H
