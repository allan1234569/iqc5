#ifndef PV_REPORTABLERANGE_H
#define PV_REPORTABLERANGE_H

#include <QDialog>

namespace Ui {
class Pv_ReportableRange;
}

class Pv_ReportableRange : public QDialog
{
    Q_OBJECT

public:
    explicit Pv_ReportableRange(QWidget *parent = 0);
    void showTable();
    ~Pv_ReportableRange();

protected:
    void closeEvent(QCloseEvent *event);
private:
    Ui::Pv_ReportableRange *ui;
};

#endif // PV_REPORTABLERANGE_H
