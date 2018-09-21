#ifndef EDITMETHOD_H
#define EDITMETHOD_H


#include <QDialog>

namespace Ui {
class EditMethod;
}

class EditMethod : public QDialog
{
    Q_OBJECT

public:
    explicit EditMethod(QWidget *parent = 0);
    ~EditMethod();
    void SetModel(QString id);
    void SetName(QString name);

private slots:
    void on_btnCancel_clicked();

    void on_btnOK_clicked();

    void on_inputSubject_currentIndexChanged(int index);

private:
    Ui::EditMethod *ui;
    QString methodId;
};

#endif // EDITMETHOD_H
