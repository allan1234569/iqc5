#ifndef W_DA7600_H
#define W_DA7600_H

#include "basewindow.h"

class W_DA7600 : public BaseWindow
{
    Q_OBJECT

public:
    W_DA7600(QWidget *parent = 0);
    ~W_DA7600();

    // BaseWindow interface
public:
    void loadConfig();
    int file_decode(const QString &as_filepath);

private:
    int m_nWellIndex;
    quint32 m_nSampleNoIndex;
    quint32 m_nResultIndex;
    quint32 m_nTypeIndex;

    QString m_sIsStartWell;
    QString m_sIsSampleType;

    // BaseWindow interface
public:
    void set_TableWidgetHeader();

private slots:
    void on_Import_PushButton_clicked();
};

#endif // W_DA7600_H
