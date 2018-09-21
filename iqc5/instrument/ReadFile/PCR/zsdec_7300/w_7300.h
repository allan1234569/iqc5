#ifndef W_7300_H
#define W_7300_H

#include "basewindow.h"

class W_7300 : public BaseWindow
{
    Q_OBJECT

public:
    W_7300(QWidget *parent = 0);
    ~W_7300();

    // BaseWindow interface
public:
    void loadConfig();
    int file_decode(const QString &filepath);

private:
    int m_nResultIndex;
    int m_nWellIndex;
    int m_nsampleNoIndex;

    // BaseWindow interface
public:
    void set_TableWidgetHeader();

private slots:
    void on_Import_PushButton_clicked();
};

#endif // W_7300_H
