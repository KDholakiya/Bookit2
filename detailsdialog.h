#ifndef DETAILSDIALOG_H
#define DETAILSDIALOG_H

#include <QDialog>

namespace Ui {
class detailsDialog;
}

class detailsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit detailsDialog(QWidget *parent = nullptr);
    ~detailsDialog();
    bool setWid(QWidget* wid);
    void showDialog();
    void clearDialog();
private:
    QWidget *Wid;
    Ui::detailsDialog *ui;
};

#endif // DETAILSDIALOG_H
