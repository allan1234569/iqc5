#ifndef CHARTTITLIBAR_H
#define CHARTTITLIBAR_H

#include <QWidget>

namespace Ui {
class ChartTitliBar;
}

class ChartTitliBar : public QWidget
{
    Q_OBJECT

public:
    explicit ChartTitliBar(QWidget *parent = 0);
    ~ChartTitliBar();

private slots:
    void on_btnExport_clicked();

    void on_btnExportByType_clicked();

private:
    Ui::ChartTitliBar *ui;
};

#endif // CHARTTITLIBAR_H
