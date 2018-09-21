#ifndef W_5195R_H
#define W_5195R_H

#include "basewindow.h"

class W_5195R : public BaseWindow
{
    Q_OBJECT

public:
    W_5195R(QWidget *parent = 0);
    ~W_5195R();


    // BaseWindow interface
public:
    void set_TableWidgetHeader();

    void file_decode(const QString as_file, const QString as_path);

    void excel_file_decode(const QString as_filepath);

    void loadConfig();

private slots:
    void on_Import_PushButton_clicked();

private:
    QString m_sFileType;

    qint32 m_nSampleNoIndex;

    qint32 m_nItemCnt;
    QList<QString>  m_slItemName;
    QList<qint32>      m_nlItemIndex;



};

#endif // W_5195R_H
