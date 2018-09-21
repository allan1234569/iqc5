#ifndef MAGLUMI2000_SETUP_H
#define MAGLUMI2000_SETUP_H

#include "asetupdialog.h"
#include <QLabel>
#include <QLineEdit>

class Maglumi2000_Setup : public ASetupDialog
{
    Q_OBJECT
public:
    explicit Maglumi2000_Setup(QWidget *parent = 0);

signals:

public slots:

    // ASetupDialog interface
public:
    void loadConfig();

    void saveConfig();

protected slots:
    void on_Ensure_PushButton_clicked();

private:
    QLabel *label;
    QLineEdit *filePath_LineEdit;
};

#endif // MAGLUMI2000_SETUP_H
