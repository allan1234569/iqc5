#ifndef W_MPC1_H
#define W_MPC1_H

#include "basewindow.h"
#include <QLineEdit>
#include <QLabel>

class W_Mpc1 : public BaseWindow
{
    Q_OBJECT

public:
    W_Mpc1(QWidget *parent = 0);
    ~W_Mpc1();

    void resetUi();

    // BaseWindow interface
public:
    void set_TableWidgetHeader();

    void file_decode(const QString as_file, const QString as_path);

    void excel_file_decode(const QString as_filepath);

private slots:
    void on_Select_PushButton_clicked();

    void on_Import_PushButton_clicked();

    void on_Refresh_PushButton_clicked();

private:
    QLineEdit *sampleMin_LineEdit;
    QLineEdit *sampleMax_LineEdit;
    QLabel *line_Label;

};

#endif // W_MPC1_H
