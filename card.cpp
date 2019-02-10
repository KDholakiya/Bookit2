#include "card.h"
#include "ui_card.h"
#include <QPixmap>
#include <QLabel>
#include <QBrush>
#include <QPalette>
#include "dataprovider.h"
#include <QDebug>
#include <mainwindow.h>
#include "detailsviewer.h"
card::card(QWidget *parent) : QWidget(parent), ui(new Ui::card){
    ui->setupUi(this);
    par=parent;
}

void card::wid(QByteArray raw_data, QString title,QString Size,bool implimentFilters){
    QSize size=(Size=="xs") ? QSize(50,50)
                            :(Size=="s") ? QSize(100,200)
                                         : (Size=="m") ? QSize(190,273)
                                                       : ( (Size=="xl") ? QSize (230,330)
                                                                        : ((Size=="xxl") ? QSize(330,430)
                                                                                         :  QSize(190,273)));

    this->setMaximumSize(size);
    this->setMinimumSize(184,255);
    QPixmap pic;
    pic.loadFromData(raw_data);
    ui->pix->resize(pic.width(),pic.height());
    ui->pix->setPixmap(pic);
    ui->pix->setScaledContents(true);
    if(title=="no title") delete ui->title;
    else ui->title->setText(title);
    ui->pix->setObjectName(title);
    if(implimentFilters)  ui->pix->installEventFilter(this);
    shadow->setBlurRadius(4);
    shadow->setOffset(3,3);
    shadow->setColor(QColor("#adadad"));
    ui->pix->setGraphicsEffect(shadow);
}

card::~card(){
    delete ui;
}

bool card::eventFilter(QObject *obj, QEvent *event){
    if(event->type()==QEvent::MouseButtonRelease){
           detailsViewer *dv=new detailsViewer(par);
           dv->details(this->data,this->poster);
    }
    if(event->type()==QEvent::Enter){
        shadow->setBlurRadius(4);
        shadow->setOffset(4,4);
        shadow->setColor(QColor("#adadad"));
        ui->pix->setGraphicsEffect(shadow);
    }
    if(event->type()==QEvent::Leave){
        shadow->setBlurRadius(4);
        shadow->setOffset(3,3);
        shadow->setColor(QColor("#adadad"));
        ui->pix->setGraphicsEffect(shadow);
    }
    return false;
}
