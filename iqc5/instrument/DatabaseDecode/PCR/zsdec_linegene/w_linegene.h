#ifndef W_LINEGENE_H
#define W_LINEGENE_H

#include <QWidget>
#include "basewindow.h"


class W_Linegene : public BaseWindow
{
    Q_OBJECT

public:
    W_Linegene(QWidget *parent = 0);
    ~W_Linegene();

    // BaseWindow interface
public:
//    void loadConfig();
    int decode(const QString &data);

public slots:
    void slt_timeout();

    void slt_setQuery();
};

#endif // W_LINEGENE_H
