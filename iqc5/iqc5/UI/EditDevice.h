#ifndef EDITDEVICE_H
#define EDITDEVICE_H

#include <QDialog>

namespace Ui {
class EditDevice;
}

class EditDevice : public QDialog
{
    Q_OBJECT
    
public:
    explicit EditDevice(QWidget *parent = 0);
    ~EditDevice();
    void SetModel(QString id);
    void SetName(QString name);

private slots:
    void on_btnOK_clicked();
    void on_btnCancel_clicked();
    void on_inputBrand_currentIndexChanged(int index);

private:
    Ui::EditDevice *ui;
    QString deviceId;
};

#endif // EDITDEVICE_H
