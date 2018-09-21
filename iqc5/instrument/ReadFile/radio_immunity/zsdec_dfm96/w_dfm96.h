#ifndef W_DFM96_H
#define W_DFM96_H

#include "basewindow.h"

class W_Dfm96 : public BaseWindow
{
    Q_OBJECT

public:
    W_Dfm96(QWidget *parent = 0);
    ~W_Dfm96();

    // BaseWindow interface
public:
    void set_TableWidgetHeader();

    int file_decode(const QString &as_file, const QString as_path);

    void file_decode_new(const QString &as_file, const QString as_path);

    void loadConfig();

private slots:
    void on_Import_PushButton_clicked();

private:
    bool m_bNewMode;

};

#endif // W_DFM96_H
