#ifndef CARD_H
#define CARD_H

#include <QWidget>
#include "mainwindow.h"
#include <QGraphicsDropShadowEffect>

namespace Ui {
class card;
}

class card : public QWidget
{
    Q_OBJECT

public:
    explicit card(QWidget *parent = nullptr);
    void wid(QByteArray raw_data,QString title="no title",QString Size="m",bool implimentFilters=true);
    QMap<QString , QVariant> data;
    QVariant poster;
    QWidget* par;
    ~card();
protected:
    bool eventFilter(QObject *obj, QEvent *event);
private:
    QGraphicsDropShadowEffect *shadow=new QGraphicsDropShadowEffect;

    Ui::card *ui;
    MainWindow *mv;
};

#endif // CARD_H
