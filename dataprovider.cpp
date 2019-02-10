#include "dataprovider.h"

dataProvider::dataProvider(){}

QVariant dataProvider::request(QString requestString)
{
    qDebug()<<requestString;
    QUrl url("http://localhost/bookit(backend)/rest/?thisIsAnPassword/"+requestString);
    //QUrl url("http://bookit123.000webhostapp.com/rest/?thisIsAnPassword/"+requestString);

    QNetworkRequest req(url);
    QNetworkAccessManager *nam=new QNetworkAccessManager;
    req.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    req.setAttribute(QNetworkRequest::FollowRedirectsAttribute,true);
    QNetworkReply *reply=nam->get(req);
    while(!reply->isFinished()){
        qApp->processEvents();
    }
    QByteArray rawData=reply->readAll();
    if(requestString.contains("poster")){
        return rawData;
    }else{
        QJsonDocument json=QJsonDocument::fromJson(rawData);
        return json;
    }
}

