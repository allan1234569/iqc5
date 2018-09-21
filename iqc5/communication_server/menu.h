#ifndef MENU_H
#define MENU_H

#include <QMenu>

class Menu : public QMenu
{
    Q_OBJECT
public:
    explicit Menu(QWidget *parent = 0);

signals:

public slots:


    // QObject interface
public:
    bool event(QEvent *e);
};

#endif // MENU_H
