#ifndef PV_ACCURACYPLOT_H
#define PV_ACCURACYPLOT_H

#include <QDialog>

namespace Ui {
class Pv_AccuracyPlot;
}

class Pv_AccuracyPlot : public QDialog
{
    Q_OBJECT

public:
    explicit Pv_AccuracyPlot(QWidget *parent = 0);
    void showChart();
    void showDValueChart();
    ~Pv_AccuracyPlot();

private:
    Ui::Pv_AccuracyPlot *ui;
};

#endif // PV_ACCURACYPLOT_H
