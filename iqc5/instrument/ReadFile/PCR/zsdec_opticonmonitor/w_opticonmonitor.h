#ifndef W_OPTICONMONITOR_H
#define W_OPTICONMONITOR_H

#include "basewindow.h"

class W_Opticonmonitor : public BaseWindow
{
    Q_OBJECT

public:
    W_Opticonmonitor(QWidget *parent = 0);
    ~W_Opticonmonitor();

    // BaseWindow interface
public:
    void set_TableWidgetHeader();

private slots:
    void on_Import_PushButton_clicked();

    void slt_getClipboard();
};

#endif // W_OPTICONMONITOR_H
