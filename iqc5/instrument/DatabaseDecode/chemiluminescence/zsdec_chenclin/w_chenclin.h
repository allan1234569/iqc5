#ifndef W_CHENCLIN_H
#define W_CHENCLIN_H

#include "basewindow.h"

class W_Chenclin : public BaseWindow
{
    Q_OBJECT

public:
    W_Chenclin(QWidget *parent = 0);
    ~W_Chenclin();

    // BaseWindow interface
public:
    void set_TableWidgetHeader();
    void file_decode(const QString as_file, const QString as_path);
    void excel_file_decode(const QString as_filepath);

private slots:
    void on_Import_PushButton_clicked();
};

#endif // W_CHENCLIN_H
