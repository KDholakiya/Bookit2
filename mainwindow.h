#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <dataprovider.h>
#include <QPixmap>
#include "contentshoecase.h"
#include <QDebug>
#include "detailsdialog.h"
#include <QGraphicsDropShadowEffect>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool ShowDetails(QWidget* wid);

private:
    QGraphicsDropShadowEffect *shadow=new QGraphicsDropShadowEffect;

    Ui::MainWindow *ui;
    QList<QWidget *> backStack;
    bool changeShowcase(QString what,QString cat,bool fromCat=false);
    static QList<QString> LStack;
//    detailsDialog *dialog;
    QString CurrentCase="movies";
    QString CurrentCat="Trending";
    bool first;
    void changeCategories(QString what);
    void highlightselected(QObject* object);
protected:
    static QList<ContentShoecase *> PStack;

    bool eventFilter(QObject *obj, QEvent *event);
    void eventInstaller(QList<QWidget *> widList);
private slots:
    void on_menubtn_released();
    bool on_cats_currentIndexChanged(const QString &arg1);
    void on_pushButton_released();
};

#endif // MAINWINDOW_H
