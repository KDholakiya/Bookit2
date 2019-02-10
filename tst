#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    QVariant json=dataProvider::request("select/data/movies/2/2");
    qDebug()<<json.toString();
    ui->data->setPlainText(json.toString());
    QVariant binary=dataProvider::request("select/poster/movies/trending/2");
    QPixmap pix;
    pix.loadFromData(binary.toByteArray());
    ui->poster->setPixmap(pix);
    QList<QWidget *> widlist={ui->movies,ui->events,ui->plays,ui->sports};
    eventInstaller(widlist);
}
MainWindow::~MainWindow(){
    delete ui;

}

bool MainWindow::eventFilter(QObject *obj, QEvent *event){
    if(event->type()==event->MouseButtonRelease){
        if(asd->isEmpty()){
            ContentShoecase *div=new ContentShoecase;
            div->setShowCaseItems(obj->objectName());
            asd->push_front(div);
            ui->show_layout->addWidget(div);
        }else{
            if(checkStack(obj->objectName())){
                asd->at(1)->hide();
                ui->show_layout->addWidget(asd->front());
            }
        }
    }
}

bool MainWindow::checkStack(QString name)
{
    if(asd->size()==1) return true;
    for(int i=0;i<asd->size();i++){
        if(asd->at(i)->objectName()==name){
            asd->push_front(asd->takeAt(i));
            asd->removeAt(i);
            return true;
        }else{
            ContentShoecase *div=new ContentShoecase;
            div->setShowCaseItems(name);
            asd->push_front(div);
            return true;
        }
    }

}

void MainWindow::eventInstaller(QList<QWidget *> widList)
{
    for(int i=0;i<widList.size();i++){
        widList.at(i)->installEventFilter(this);
    }
}
