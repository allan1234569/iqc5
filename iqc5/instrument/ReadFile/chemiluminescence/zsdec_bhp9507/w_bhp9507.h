#ifndef W_BHP9507_H
#define W_BHP9507_H

#include "basewindow.h"

class W_Bhp9507 : public BaseWindow
{
    Q_OBJECT

public:
    W_Bhp9507(QWidget *parent = 0);
    ~W_Bhp9507();

    // BaseWindow interface
public:
    void file_decode(const QString as_file, const QString as_path);

    void excel_file_decode(const QString as_filepath);

    void loadConfig();

public:
    void set_TableWidgetHeader();

private slots:
    void on_Import_PushButton_clicked();

private:
    qint32 m_nSampleNoIndex;
    qint32 m_nResultIndex;

    QString m_sLastItem;    //上一次的项目名

};

#endif // W_BHP9507_H
