#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "basewindow.h"
#include "singletonSocket.h"

class Mainwindow : public BaseWindow
{
    Q_OBJECT
public:
    explicit Mainwindow(QWidget *parent = 0);

public:


signals:

public slots:

private:



    // BaseWindow interface
protected:
    void decode(const QString &data);
};

#endif // MAINWINDOW_H
