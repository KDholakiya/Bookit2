#ifndef INVOICE_H
#define INVOICE_H

#include <QList>
class invoice
{
public:
    invoice( QList<QString> list);
    bool fireData();
private:
    QList<QString> List;
};


#endif // INVOICE_H
