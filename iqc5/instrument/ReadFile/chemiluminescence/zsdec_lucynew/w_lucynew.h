#ifndef W_LUCYNEW_H
#define W_LUCYNEW_H

#include "basewindow.h"

class W_Lucynew : public BaseWindow
{
    Q_OBJECT

public:
    W_Lucynew(QWidget *parent = 0);
    ~W_Lucynew();

    // BaseWindow interface
public:
    void set_TableWidgetHeader();

    void file_decode(const QString as_file, const QString as_path);

    void excel_file_decode(const QString as_filepath);

private slots:
    void on_Import_PushButton_clicked();
};

#endif // W_LUCYNEW_H
