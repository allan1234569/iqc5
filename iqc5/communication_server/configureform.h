#ifndef CONFIGUREFORM_H
#define CONFIGUREFORM_H

#include <QWidget>

namespace Ui {
class configureForm;
}

class configureForm : public QWidget
{
    Q_OBJECT

public:
    explicit configureForm(QWidget *parent = 0);
    ~configureForm();

    void apply_settings();

private:
    Ui::configureForm *ui;

signals:

public slots:
    void on_selectButton_clicked();
    void on_confirmButton_clicked();
    void on_cancelButton_clicked();



};

#endif // CONFIGUREFORM_H
