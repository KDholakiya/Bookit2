#include "paymentwindow.h"
#include "ui_paymentwindow.h"
#include <QDebug>
#include <card.h>
#include "checkout.h"
PaymentWindow::PaymentWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PaymentWindow)
{    this->setWindowTitle("Bookit");

    ui->setupUi(this);
}

PaymentWindow::~PaymentWindow()
{
    delete ui;
}

bool PaymentWindow::setInfo(QMap<QString, QVariant> data, QVariant poster, int totalTickets)
{
    Data=data;
    QPixmap pix;
    pix.loadFromData(poster.toByteArray());
    ui->poster->setPixmap(pix);
    ui->poster->setScaledContents(1);
    QMapIterator <QString , QVariant> iterator(data);
    price = data["Ticket Price"].toString().toInt();
    payable=totalTickets*price;
    for(int i=0;i<4;i++){
        iterator.next();
        if(iterator.key().contains('$')){
            if(iterator.key().contains("Venue")){
                ui->place->setText(iterator.value().toString());
                continue;
            }
            if(iterator.key().contains("Date")){
                ui->Date->setText(iterator.value().toString());
                continue;
            }else{
                ui->Time->setText(iterator.value().toString());
                continue;
            }
        }
    }
    gst=(payable * 18)/100;
    conFee=(payable * 10)/100;
    payable+=gst+conFee;
    ui->title->setText(data["Name"].toString());
    length=totalTickets;
    ui->price->setText(QString::number(price));
    ui->ticketLength->setText(QString::number(length)+" Tickets = ");
    ui->totalOrder->setText(QString::number(payable));
    ui->ticketTotal->setText(QString::number(price*length));
    ui->gst->setText(QString::number(gst));
    ui->convFees->setText(QString::number(conFee));
}

void PaymentWindow::on_PayProcess_released()
{
    this->window()->close();
    (static_cast<QWidget *>(this->parent()->parent()))->close();
    Checkout *checkout=new Checkout;
    QList<int> rakams={price,length,gst,conFee,payable};
    checkout->Data=Data;
    checkout->Rakams=rakams;
    checkout->exec();
}
