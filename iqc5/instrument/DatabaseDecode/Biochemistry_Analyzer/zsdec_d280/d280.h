#ifndef D280_H
#define D280_H

#include "basewindow.h"


class D280 : public BaseWindow
{
    Q_OBJECT

public:
    D280(QWidget *parent = 0);
    ~D280();

    // BaseWindow interface
public:
    int decode(const QString &data);

public slots:
    void slt_setQuery();

private:
    Ui::BaseWindow *parentUi;


    // BaseWindow interface
public:
    void loadConfig();

    // BaseWindow interface
private slots:
    void on_Select_PushButton_clicked();
};

#endif // D280_H
