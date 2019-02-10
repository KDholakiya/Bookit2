#include "detailsviewer.h"
#include "ui_detailsviewer.h"
#include <QDebug>
#include <QJsonDocument>
#include  "mainwindow.h"
#include <card.h>
#include "paymentwindow.h"
detailsViewer::detailsViewer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::detailsViewer)
{
    ui->setupUi(this);
}

bool detailsViewer::details(QMap<QString , QVariant> data, QVariant poster)
{
    Data=data;
    Poster=poster;

    card *pix=new card();
    pix->wid(poster.toByteArray(),"no title","xxl",false);
    ui->pic->addWidget(pix);

    QList<QLabel *> labels={ui->ALabel,ui->BLabel,ui->CLabel,ui->DLabel};
    QList<QLabel *> texts={ui->AText,ui->BText,ui->CText,ui->DText};

    ui->title->setText(data["Name"].toString());
    ui->synopsis->setText("<b style='font-size:12pt;color:rgb(89, 65, 169);'>Synopsis : </b>"+data["synopsis"].toString());
    ui->price->setText(data["Ticket Price"].toString());
    ui->total->setText(data["Ticket Price"].toString());
    QMapIterator <QString , QVariant> iterator(data);
    for(int i=0;i<4;i++){
        iterator.next();
        if(iterator.key().contains('$')){
            labels.at(i)->setText(iterator.key().right(iterator.key().length()-2)+" : ");
            texts.at(i)->setText(iterator.value().toString());
        }
    }
    payable=data["Ticket Price"].toString().toInt();
    price=data["Ticket Price"].toString().toInt();

    dialog->setWid(this);
    dialog->showDialog();
}

detailsViewer::~detailsViewer()
{
    delete ui;
}

void detailsViewer::on_bookBtn_released()
{
    pay=new PaymentWindow(this);
    pay->setInfo(Data,Poster,length);
    pay->exec();
}

void detailsViewer::on_ticketPlus_released()
{
    if(length < 10){
        length++;
        ui->ticketLength->setText(QString::number(length));
        payable=payable+price;
        ui->total->setText(QString::number(payable));
    }
}

void detailsViewer::on_ticketMinus_released()
{
    if(length > 1){
        length--;
        ui->ticketLength->setText(QString::number(length));
        payable=payable-price;
        ui->total->setText(QString::number(payable));
    }
}

void detailsViewer::on_addToWatchlistBtn_released()
{
    qDebug()<<Data["what"].toString()<<Data["id"].toString();
}
