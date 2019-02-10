#include "seatselection.h"
#include "ui_seatselection.h"

seatSelection::seatSelection(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::seatSelection)
{
    ui->setupUi(this);
}

seatSelection::~seatSelection()
{
    delete ui;
}

void seatSelection::addData(QMap<QString, QVariant> data)
{
    ui->Movie->setText(data["Name"].toString());
}
