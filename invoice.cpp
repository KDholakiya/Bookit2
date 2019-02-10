#include "invoice.h"
#include <QDebug>
#include <QtNetwork>
invoice::invoice(QList<QString> list)
{
    List=list;
}

bool invoice::fireData()
{
    QString url;
    url="http://bookit123.000webhostapp.com/rest/?thisIsAnPassword/addTicket";
    //url="http://localhost/bookit/rest/?thisIsAnPassword/addTicket";
    for(int i=0;i<List.length();i++){
        url.append("/"+List.at(i));
    }
    qDebug()<<url;
    QNetworkRequest req(url);
    req.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    req.setAttribute(QNetworkRequest::FollowRedirectsAttribute,true);
    QNetworkAccessManager nam;
    QNetworkReply *reply=nam.get(req);
    while(!reply->isFinished()) qApp->processEvents();
    QByteArray ba=reply->readAll();
    QString r=ba.toHex();
    if(r=="true"){
        return true;
    }else if(r=="false"){
        return false;
    }
}

