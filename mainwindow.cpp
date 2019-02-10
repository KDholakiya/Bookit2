#include "mainwindow.h"
#include "ui_mainwindow.h"
QList<ContentShoecase *> MainWindow::PStack;
QList<QString> MainWindow::LStack;
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    QList<QWidget *> widlist={ui->Movies,ui->Events,ui->Plays,ui->Sports,ui->watchList};
    eventInstaller(widlist);
    changeShowcase("movies","Trending");
    shadow->setBlurRadius(4);
    shadow->setOffset(2,2);
    shadow->setColor(QColor("#000"));
    ui->Movies->setGraphicsEffect(shadow);\
    this->setWindowTitle("Bookit");
}
MainWindow::~MainWindow(){ delete ui; }

bool MainWindow::ShowDetails(QWidget* wid)
{
    //show saparate dialog
    //dialog = new detailsDialog();
    //dialog->setWid(wid);
    //dialog->showDialog();

    //show in main window
    /*
 *  backStack.push_front(ui->widget);
 *  backStack.push_front(wid);
 *  ui->widget->hide();
 *  ui->fullbody->addWidget(wid);
*/
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event){
    //check event type
    if(event->type()==QEvent::MouseButtonRelease){
        if(obj->objectName()=="watchList"){
            if(!ui->cats->isHidden()) ui->cats->hide();
        }else ui->cats->show();

        //change showcase as clicked event
        QString what=obj->objectName().toLower();
        QString cat=(obj->objectName().toLower()=="movies") ? "Trending"  : (obj->objectName()=="watchList") ? "watchList" : "today" ;
        if(PStack.front()->objectName()!=what+cat) changeShowcase(what,cat);
        //bold selected label
        this->highlightselected(obj);
    }
    return false;
}
void MainWindow::highlightselected(QObject* object)
{

    QLabel *wid=static_cast<QLabel *>(object);



    QList <QLabel *> widlist= wid->parent()->findChildren<QLabel *>();
    QFont font("MS Shell Dlg 2",17);
    font.setBold(0);
    for(int i=0;i<widlist.size();i++){
       widlist.at(i)->setFont(font);
       shadow->setBlurRadius(0);
       widlist.at(i)->setGraphicsEffect(shadow);
    }
    font.setBold(1);
    if(wid->objectName()=="watchList") font.setPointSize(15);
    wid->setFont(font);
    shadow->setBlurRadius(4);
    shadow->setOffset(2,2);
    shadow->setColor(QColor("#000"));
    wid->setGraphicsEffect(shadow);
}
bool MainWindow::changeShowcase(QString what, QString cat,bool fromCat){
    //check clicked case is exists in stack or not

    if(!LStack.contains(what+cat)){
        ContentShoecase *showcase=new ContentShoecase(this);
        showcase->setObjectName(what+cat);
        showcase->setShowCaseItems(what,cat);
        LStack.push_front(what+cat);
        PStack.push_front(showcase);
    }else{
        PStack.push_front(PStack.takeAt(LStack.indexOf(what+cat)));
        LStack.push_front(LStack.takeAt(LStack.indexOf(what+cat)));
    }
    for(int i=0;i<PStack.size();i++) PStack.at(i)->hide();
    ui->show_layout->addWidget(PStack.front());
    CurrentCase=what;
    CurrentCat=cat;
    if(!fromCat) this->changeCategories(what);
    PStack.front()->show();
}

void MainWindow::changeCategories(QString what)
{
    ui->cats->clear();
    QStringList moviescats={"Trending","Gujarati","English","Hindi"};
    QStringList othersCats={"Today","Tomorrow","This Weekend","Next Weekend"};
    if(what == "movies"){
        ui->cats->addItems(moviescats);
    }else{
        ui->cats->addItems(othersCats);
    }
}


//event install handlers on widgets
void MainWindow::eventInstaller(QList<QWidget *> widList){
    for(int i=0;i<widList.size();i++)  widList.at(i)->installEventFilter(this);
}

void MainWindow::on_menubtn_released(){
    if(ui->menu_container->isHidden()){
        ui->menu_container->show();
        ui->menubtn->setText(("<"));
    }else{
        ui->menu_container->hide();
        ui->menubtn->setText((">"));
    }
}


bool MainWindow::on_cats_currentIndexChanged(const QString &arg1)
{
    int index=ui->cats->currentIndex();
    QStringList moviescats={"trending","gujarati","english","hindi"};
    QStringList othersCats={"today","tomorrow","this_weekend","next_weekend"};
    if(arg1.isEmpty() || moviescats[index]==CurrentCat || othersCats[index]==CurrentCat) return false;
    QString cat;
    qDebug()<<CurrentCase<<CurrentCat;
    if(CurrentCase=="movies") cat=moviescats[index];
    else if(CurrentCat=="featured") cat=moviescats[index];
    else cat=othersCats[index];
    //  qDebug()<<CurrentCase<<cat;
    changeShowcase(CurrentCase,cat,true);
}




