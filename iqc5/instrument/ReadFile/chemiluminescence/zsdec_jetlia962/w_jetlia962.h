#ifndef W_JETLIA962_H
#define W_JETLIA962_H

#include "basewindow.h"

class W_Jetlia962 : public BaseWindow
{
    Q_OBJECT

public:
    W_Jetlia962(QWidget *parent = 0);
    ~W_Jetlia962();

private:
    void resetUi();

    // BaseWindow interface
public:
    void set_TableWidgetHeader();

    void file_decode(const QString as_file, const QString as_path);

    void excel_file_decode(const QString as_filepath);

    void loadConfig();

private slots:
    void on_Select_PushButton_clicked();

    void on_Import_PushButton_clicked();

    void on_Refresh_PushButton_clicked();

private:
    QLineEdit *sampleMin_LineEdit;
    QLineEdit *sampleMax_LineEdit;
    QLabel *line_Label;


    qint32 m_nDataLen;
    qint32 m_nSampleNoStart;
    qint32 m_nSampleNolen;
    qint32 m_nItemNoStart;
    qint32 m_nItemNolen;
    qint32 m_nRestulStart;
    qint32 m_nRestulLen;
    qint32 m_nSampleDateStart;
    qint32 m_nSampleDateLen;
};

#endif // W_JETLIA962_H
