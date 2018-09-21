#ifndef E170_SETUP_H
#define E170_SETUP_H

#include "asetupdialog.h"

#include <QLabel>
#include <QComboBox>
#include <QCheckBox>

class E170_Setup : public ASetupDialog
{
    Q_OBJECT
public:
    explicit E170_Setup(QWidget *parent = 0);

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
    QComboBox *combox;
    QCheckBox *checkbox;
};

#endif // E170_SETUP_H
