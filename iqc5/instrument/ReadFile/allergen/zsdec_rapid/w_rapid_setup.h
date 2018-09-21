#ifndef W_RAPID_SETUP_H
#define W_RAPID_SETUP_H
#include "asetupdialog.h"

class W_Rapid_Setup : public ASetupDialog
{
    Q_OBJECT
public:
    explicit W_Rapid_Setup(QWidget *parent = 0);

signals:

public slots:

private:
    QLabel *label;
    QLineEdit *filepath_LineEdit;


    // ASetupDialog interface
public:
    void loadConfig();

    void saveConfig();

private slots:
    void on_Ensure_PushButton_clicked();
};

#endif // W_RAPID_SETUP_H
