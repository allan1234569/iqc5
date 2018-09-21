#ifndef WIDGET_H
#define WIDGET_H

#include "basewindow.h"

class Widget : public BaseWindow
{
    Q_OBJECT
public:
    explicit Widget(QWidget *parent = 0);

signals:

public slots:


    // BaseWindow interface
public:
    void loadConfig();
    int decode(const QString &data);

public slots:
    void slt_timeout();

    // BaseWindow interface
public slots:
    void slt_setQuery();
};

#endif // WIDGET_H
