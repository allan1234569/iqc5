#ifndef W_MX3000P_H
#define W_MX3000P_H

#include "basewindow.h"

class W_MX3000P : public BaseWindow
{
    Q_OBJECT

public:
    W_MX3000P(QWidget *parent = 0);
    ~W_MX3000P();

    // BaseWindow interface
public:
    void loadConfig();



private:
    qint32 m_nWellIndex;
    qint32 m_nResultIndex;
    qint32 m_nSampleNoIndex;
    qint32 m_nItemIndex;

    // BaseWindow interface
public:
    void set_TableWidgetHeader();

    // BaseWindow interface
private slots:
    void on_Import_PushButton_clicked();

    // BaseWindow interface
public:
    void excel_file_decode(const QString as_filepath);
};

#endif // W_MX3000P_H
