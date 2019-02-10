#ifndef DETAILSVIEWER_H
#define DETAILSVIEWER_H

#include <QWidget>
#include <QMap>
#include <QVariant>
#include "detailsdialog.h"
#include "paymentwindow.h"
namespace Ui {
class detailsViewer;
}

class detailsViewer : public QWidget
{
    Q_OBJECT

public:
    explicit detailsViewer(QWidget *parent = nullptr);
    bool details(QMap<QString , QVariant> data,QVariant poster);
    ~detailsViewer();

private slots:
    void on_bookBtn_released();

    void on_ticketPlus_released();

    void on_ticketMinus_released();

    void on_addToWatchlistBtn_released();

private:
    detailsDialog *dialog=new detailsDialog();
    PaymentWindow *pay=new PaymentWindow();

    Ui::detailsViewer *ui;
    QMap<QString , QVariant> Data;
    QVariant Poster;
    int length=1;
    int payable;
    int price;
};

#endif // DETAILSVIEWER_H
