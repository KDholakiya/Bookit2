#ifndef CHECKOUT_H
#define CHECKOUT_H

#include <QDialog>
#include <QMap>
#include <QMessageBox>

namespace Ui {
class Checkout;
}

class Checkout : public QDialog
{
    Q_OBJECT

public:
    explicit Checkout(QWidget *parent = nullptr);
    ~Checkout();
    QMap<QString,QVariant> Data;
    QList<int> Rakams;
    QString Card="Creditcard";

private:
    QMessageBox *box=new QMessageBox();

    Ui::Checkout *ui;


private slots:
    void on_pay_released();
    void generateinvoice();
    void on_pushButton_released();

    void on_deibitPay_released();

    void on_cardnmbr_textChanged(const QString &arg1);

    void on_cvv_textChanged(const QString &arg1);

    void on_creditPay_released();


};

#endif // CHECKOUT_H
