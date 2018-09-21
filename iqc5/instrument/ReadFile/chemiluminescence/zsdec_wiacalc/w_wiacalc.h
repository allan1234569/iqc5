#ifndef W_WIACALC_H
#define W_WIACALC_H

#include "basewindow.h"

class W_Wiacalc : public BaseWindow
{
    Q_OBJECT

public:
    W_Wiacalc(QWidget *parent = 0);
    ~W_Wiacalc();

    qint32 getPos(QString as_str);

    // BaseWindow interface
public:
    void set_TableWidgetHeader();

    void file_decode(const QString as_file, const QString as_path);

    void excel_file_decode(const QString as_filepath);

    void loadConfig();

private slots:
    void on_Import_PushButton_clicked();

private:
    QString m_sSampleId;
    QString m_sResult;
    QString m_sOut;

    bool m_bIsDual;
    QString m_sItem;

    qint32 m_nSampleNoPos;
    qint32 m_nSampleNoLen;
    qint32 m_nResultPos;
    qint32 m_nResultLen;

};

#endif // W_WIACALC_H
