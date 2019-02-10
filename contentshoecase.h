#ifndef CONTENTSHOECASE_H
#define CONTENTSHOECASE_H

#include <QFrame>
#include <QHBoxLayout>
namespace Ui {
class ContentShoecase;
}

class ContentShoecase : public QFrame
{
    Q_OBJECT

public:
    explicit ContentShoecase( QWidget *parent = nullptr);
    ~ContentShoecase();
    bool setShowCaseItems(QString get,QString Category,bool isQuery=false);
protected:
    bool eventFilter(QObject *obj,QEvent *event);
private:
    Ui::ContentShoecase *ui;
    QVariant Requester(QString,QString,QString,QString=nullptr);
    bool iscollapsed=false;
    QHBoxLayout* secondLay;
    bool cardManager(QMap<QString , QVariant> map,QHBoxLayout *line_layout,QString cat,QString get,int phase,QVariant data);

};

#endif // CONTENTSHOECASE_H
