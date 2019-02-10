#include "checkout.h"
#include "ui_checkout.h"
#include <QDebug>
#include "invoice.h"
Checkout::Checkout(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Checkout)
{    this->setWindowTitle("Bookit");

    ui->setupUi(this);
}

Checkout::~Checkout()
{
    delete ui;
}


void Checkout::on_pay_released()
{
    if( ( ui->cardnmbr->text().length() < 16 ) or
        ( ui->cvv->text().length() < 5 ) or
        ( ui->exMonth->currentIndex() == 0 ) or
        ( ui->exYear->currentIndex() == 0 )
    ) {
        box->critical(this,"Invalid Data","You've Enterd Invalid Data, Kindly Enter Valid Data Other Wise Your Device Will Be Blastttt...");
    }else{
        this->generateinvoice();
    }
}

void Checkout::generateinvoice(){
    QList<QString> dataToBeSend={Data["what"].toString(),
                                 Data["id"].toString(),
                                 QString::number(Rakams.at(0)),
                                 QString::number(Rakams.at(1)),
                                 QString::number(Rakams.at(2)),
                                 QString::number(Rakams.at(3)),
                                 QString::number(Rakams.at(4)),
                                 Card,
                                 ui->cardnmbr->text(),
                                 ui->cvv->text(),
                                 ui->exMonth->currentText(),
                                 ui->exYear->currentText(),
                                };
   // qDebug()<<dataToBeSend;
    invoice bill(dataToBeSend);
    if(bill.fireData()){
        box->information(this,"Done...","Successfully Booked Ticket. Soon You'll Recieve Invoice via Email");
    }else{
        box->information(this,"Error","Try Again After Some Time");
    }
    this->window()->close();
}

void Checkout::on_pushButton_released()
{
    this->window()->close();
}

void Checkout::on_deibitPay_released()
{
    Card="Debitcard";
    ui->deibitPay->setStyleSheet("border:2px solid rgb(89, 65, 169);"
                                 "border-radius:7px;"
                                 "background-color:rgb(89, 65, 169);");
    ui->creditPay->setStyleSheet("border:2px solid rgb(89, 65, 169);"
                                 "border-radius:7px;");
    ui->cardNumbertype->setText("Enter Debitcard Number :");
}
void Checkout::on_creditPay_released()
{
    Card="Creditcard";
    ui->creditPay->setStyleSheet("border:2px solid rgb(89, 65, 169);"
                                 "border-radius:7px;"
                                 "background-color:rgb(89, 65, 169);");
    ui->deibitPay->setStyleSheet("border:2px solid rgb(89, 65, 169);"
                                 "border-radius:7px;");
    ui->cardNumbertype->setText("Enter Creditcard Number :");
}
void Checkout::on_cardnmbr_textChanged(const QString &arg1){
    if(arg1.isEmpty()) return;
    if( !(arg1.at(arg1.length() - 1).isDigit()) ) ui->cardnmbr->setText(ui->cardnmbr->text().remove(arg1.length() - 1,1));
}

void Checkout::on_cvv_textChanged(const QString &arg1){
    if(arg1.isEmpty()) return;
    if( !(arg1.at(arg1.length() - 1).isDigit()) ) ui->cvv->setText(ui->cvv->text().remove(arg1.length() - 1,1));
}
