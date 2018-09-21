#ifndef CONFIGCOLUMN_H
#define CONFIGCOLUMN_H

#include <QMainWindow>

namespace Ui {
class ConfigColumn;
}

class ConfigColumn : public QMainWindow
{
    Q_OBJECT

public:
    explicit ConfigColumn(QWidget *parent = 0);
    ~ConfigColumn();

private slots:
    void on_pushButton_2_clicked();

    void on_btnSave_clicked();

private:
    Ui::ConfigColumn *ui;

    QObjectList list;
};

#endif // CONFIGCOLUMN_H
