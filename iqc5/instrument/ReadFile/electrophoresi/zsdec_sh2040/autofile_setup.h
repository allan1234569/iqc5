#ifndef AUTOFILE_SETUP_H
#define AUTOFILE_SETUP_H

#include "asetupdialog.h"

class AutoFile_Setup : public ASetupDialog
{
public:
    AutoFile_Setup(QWidget *parent = 0);

    void loadConfig();

    void saveConfig();

    // ASetupDialog interface
private slots:
    void on_Ensure_PushButton_clicked();

private:
    QLabel *label;
    QLineEdit *lineEdit;


};

#endif // AUTOFILE_SETUP_H
