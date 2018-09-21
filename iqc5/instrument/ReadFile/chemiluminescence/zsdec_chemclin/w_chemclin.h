#ifndef W_CHEMCLIN_H
#define W_CHEMCLIN_H

#include "basewindow.h"

class W_Chemclin : public BaseWindow
{
    Q_OBJECT

public:
    W_Chemclin(QWidget *parent = 0);
    ~W_Chemclin();

    // BaseWindow interface
public:
    void set_TableWidgetHeader();

    void file_decode(const QString as_file, const QString as_path);

    void excel_file_decode(const QString as_filepath);

private slots:
    void on_Import_PushButton_clicked();
};

#endif // W_CHEMCLIN_H
