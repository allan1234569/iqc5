#ifndef W_5700_H
#define W_5700_H

#include "basewindow.h"

class W_5700 : public BaseWindow
{
    Q_OBJECT

public:
    W_5700(QWidget *parent = 0);
    ~W_5700();

    // BaseWindow interface
public:
    int file_decode(const QString &filepath);

    void loadConfig();

private:
    int m_nWellIndex;
    int m_nResultIndex;


    // BaseWindow interface
public:
    void set_TableWidgetHeader();

private slots:
    void on_Import_PushButton_clicked();
};

#endif // W_5700_H
