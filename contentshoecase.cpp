#include "contentshoecase.h"
#include "ui_contentshoecase.h"
#include "card.h"
#include "dataprovider.h"
#include <QHBoxLayout>
#include <QLabel>
ContentShoecase::ContentShoecase(QWidget *parent) : QFrame(parent), ui(new Ui::ContentShoecase){
    ui->setupUi(this);
   // this->installEventFilter(this);
}

ContentShoecase::~ContentShoecase(){
    delete ui;
}

bool ContentShoecase::setShowCaseItems(QString get,QString Category, bool isQuery){
    QVariant raw_data;
    QJsonDocument raw_json;
    QList<QVariant> list;
    if(isQuery){
        //
    }else{
        if(get=="watchlist"){
            QLabel *lab=new QLabel("I've No Time For Impliment This Feature...,\nNo Panic..! i will Do it Later ",this);
            ui->verticalLayout->addWidget(lab);
        }else{
             raw_data=Requester(get,Category,"data","10");
             raw_json=raw_data.toJsonDocument();
             list=raw_json.toVariant().toList();

             //Get of Parent braces while creating watch later feature
             if( ! list.isEmpty() ){
                 int count=list.size();
                 int lines=0;
                 do{ QHBoxLayout* line_layout=new QHBoxLayout;
                     line_layout->setSpacing(6);
                     line_layout->setContentsMargins(0,0,0,6);
                     int loop=count < 5 ? count : 5;
                     for(int i=0;i<loop;i++){
                         QMap<QString , QVariant> map=list.takeAt(0).toMap();
                         this->cardManager(map,line_layout,Category,get,lines,raw_data);
                         count--;
                     }
                     ui->verticalLayout->addLayout(line_layout);
                     lines++;
                 }while(count!=0);
                 return true ;
             }else{
                 QLabel *lab=new QLabel("Nothing TO Show",this);
                 ui->verticalLayout->addWidget(lab);
             }
        }
    }
}

bool ContentShoecase::eventFilter(QObject *obj, QEvent *event){
    //Handle Resize and Do partition accrding to szize
    if(event->type()==QEvent::Resize){
        static card *childX=new card;//273h x 190w card
        QLayout *lay=ui->verticalLayout->findChild<QLayout *>("firstLayout");
        //convert normal event into resize event
        QResizeEvent *resizeEvent = static_cast<QResizeEvent*>(event);
        //get current size of this component
        int h=resizeEvent->size().height();
        //int w=resizeEvent->size().width();
        if( (resizeEvent->oldSize().height() < resizeEvent->size().height())
                && (lay->count()>6)
                && (h/2>childX->height()-50) && !iscollapsed){
            secondLay=new QHBoxLayout;
            //reverse loop through and fetch half widgets
            const int count=lay->count();
            for(int i=count-1;i>=count/2;i--) secondLay->addWidget(lay->itemAt(i)->widget());
            //ui->verticalLayout->addLayout(secondLay);
            iscollapsed=true;
        }
    }
    if(this->size().height() > 500){
        if(iscollapsed){
            if(!secondLay->isEmpty()){
                QLayout *lay=ui->verticalLayout->findChild<QLayout *>("firstLayout");
                const int count=secondLay->count();
                for(int i=0;i<count;i++) lay->itemAt(i)->widget()->hide();
            }
            iscollapsed=false;
        }
    }
}

QVariant ContentShoecase::Requester(QString get,QString Category,QString what,QString id){
    get="select/"+what+"/"+get+"/"+Category+"/"+id;
    dataProvider *req=new dataProvider;
    QVariant raw_data=req->request(get);
    return raw_data;
}

bool ContentShoecase::cardManager(QMap<QString , QVariant> map,QHBoxLayout *line_layout,QString cat,QString get,int phase,QVariant data){
    card *set=new card(static_cast<QWidget *>(this->parent()));
    QVariant raw_binary=Requester(get,cat,"poster",map["id"].toString());

    set->data=map;
    set->poster=raw_binary;
    set->wid(raw_binary.toByteArray(),map["Name"].toString(),"m");
    line_layout->setObjectName("line_layout"+QString::number(phase));
    set->setObjectName("card_"+map["name"].toString());
    line_layout->addWidget(set);
}












