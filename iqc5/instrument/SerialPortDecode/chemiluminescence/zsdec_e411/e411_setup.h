#ifndef E411_SETUP_H
#define E411_SETUP_H

#include "asetupdialog.h"

class E411_Setup : public ASetupDialog
{
    Q_OBJECT
public:
    explicit E411_Setup(QWidget *parent = 0);

signals:

public slots:

    // ASetupDialog interface
public:
    void loadConfig();

    void saveConfig();

protected slots:
    void on_Ensure_PushButton_clicked();

private:
    QLabel *sampleLabel;
    QLabel *resultLabel;
    QComboBox *sample_Combox;
    QComboBox *result_Combox;

};

#endif // E411_SETUP_H
