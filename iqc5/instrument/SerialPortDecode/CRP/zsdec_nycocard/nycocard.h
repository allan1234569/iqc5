#ifndef NYCOCARD_H
#define NYCOCARD_H

#include "basewindow.h"

class Nycocard : public BaseWindow
{
    Q_OBJECT

private:
    QString ls_etx;
    QString ls_stx;
    qint32 li_sampleNo;

public:
    explicit Nycocard(QWidget *parent = 0);

signals:

public slots:


    // BaseWindow interface
public:
    void loadConfig();

protected:
    void decode(QString &data);


};

#endif // NYCOCARD_H
