#ifndef W_7500_H
#define W_7500_H

#include <basewindow.h>

class W_7500 : public BaseWindow
{
    Q_OBJECT

public:
    explicit W_7500(QWidget *parent = 0);
    ~W_7500();


    // BaseWindow interface
public:
    void loadConfig();
    int file_decode(const QString &filepath);

private:
    int m_nWellIndex;
    int m_nSampleNoIndex;
    int m_nResultIndex;

    // BaseWindow interface
public:
    void set_TableWidgetHeader();

private slots:
    void on_Import_PushButton_clicked();
};

#endif // W_7500_H
