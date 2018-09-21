#ifndef EDITGROUP_H
#define EDITGROUP_H

#include <QDialog>

namespace Ui {
class EditGroup;
}

class EditGroup : public QDialog
{
    Q_OBJECT

public:
    explicit EditGroup(QWidget *parent = 0);
    ~EditGroup();
    void SetModel(QString id);

private slots:
    void on_btnOK_clicked();

    void on_btnCancel_clicked();

    void on_inputHospital_currentIndexChanged(int index);
    void on_inputSection_currentIndexChanged(int index);

private:
    Ui::EditGroup *ui;
    QString groupId;
};

#endif // EDITGROUP_H
