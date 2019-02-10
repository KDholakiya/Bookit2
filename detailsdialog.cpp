#include "detailsdialog.h"
#include "ui_detailsdialog.h"

detailsDialog::detailsDialog(QWidget *parent):
      QDialog(parent),
      ui(new Ui::detailsDialog)
{
    this->setWindowTitle("Bookit");

    ui->setupUi(this);
}

detailsDialog::~detailsDialog()
{
    delete ui;
}

bool detailsDialog::setWid(QWidget *wid)
{
    ui->layout->addWidget(wid);
    Wid=wid;
}

void detailsDialog::showDialog()
{
    this->exec();
}

void detailsDialog::clearDialog()
{
    if(Wid) delete Wid;
}

