#ifndef W_FJ2008PS_H
#define W_FJ2008PS_H

#include "basewindow.h"

class W_Fj2008ps : public BaseWindow
{
    Q_OBJECT

public:
    W_Fj2008ps(QWidget *parent = 0);
    ~W_Fj2008ps();

    // BaseWindow interface
public:
    void set_TableWidgetHeader();

    int file_decode(const QString &as_file, const QString as_path);

private slots:
    void on_Import_PushButton_clicked();
};

#endif // W_FJ2008PS_H
