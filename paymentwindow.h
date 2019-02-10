#ifndef PAYMENTWINDOW_H
#define PAYMENTWINDOW_H

#include <QDialog>
#include <QMap>
namespace Ui {
class PaymentWindow;
}

class PaymentWindow : public QDialog
{
    Q_OBJECT

public:
    explicit PaymentWindow(QWidget *parent = nullptr);
    ~PaymentWindow();
    bool setInfo(QMap<QString,QVariant> data,QVariant poster, int totalTickets=0);
private slots:
    void on_PayProcess_released();

private:
    QMap<QString , QVariant> Data;
    int payable;
    int length;
    int price;
    int gst;
    int conFee;
    Ui::PaymentWindow *ui;
};

#endif // PAYMENTWINDOW_H
