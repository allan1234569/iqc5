#ifndef EDITSECTION_H
#define EDITSECTION_H

#include <QDialog>

namespace Ui {
class EditSection;
}

class EditSection : public QDialog
{
    Q_OBJECT

public:
    explicit EditSection(QWidget *parent = 0);
    ~EditSection();
    void SetModel(QString id);

private slots:
    void on_btnOK_clicked();

    void on_btnCancel_clicked();

    void on_inputHospital_currentIndexChanged(int index);

private:
    Ui::EditSection *ui;
    QString sectionId;
};

#endif // EDITSECTION_H
