#ifndef SEATSELECTION_H
#define SEATSELECTION_H

#include <QWidget>

namespace Ui {
class seatSelection;
}

class seatSelection : public QWidget
{
    Q_OBJECT

public:
    explicit seatSelection(QWidget *parent = nullptr);
    ~seatSelection();
    void addData(QMap<QString , QVariant> data);
private:
    Ui::seatSelection *ui;
};

#endif // SEATSELECTION_H
