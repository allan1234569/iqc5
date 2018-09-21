#ifndef ES2010_SETUP_H
#define ES2010_SETUP_H

#include "asetupdialog.h"

#include <QLabel>
#include <QComboBox>
#include <QCheckBox>

class Es2010_setup : public ASetupDialog
{
    Q_OBJECT
public:
    explicit Es2010_setup(QWidget *parent = 0);

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
    QCheckBox *checkBox;
};

#endif // ES2010_SETUP_H
