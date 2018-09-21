#ifndef EDITTYPE_H
#define EDITTYPE_H

#include <QDialog>

namespace Ui {
class EditType;
}

class EditType : public QDialog
{
    Q_OBJECT
    
public:
    explicit EditType(QWidget *parent = 0);
    ~EditType();
    void SetModel(QString id);
    
private slots:
    void on_btnCancel_clicked();

    void on_btnOK_clicked();

    void on_inputCategory_currentIndexChanged(int index);

    void on_inputSubject_currentIndexChanged(int index);

private:
    Ui::EditType *ui;
    QString testTypeId;
};

#endif // EDITTYPE_H
