#ifndef CUSTOMQWTPLOT_H
#define CUSTOMQWTPLOT_H

#include <QWidget>
#include <qwt.h>
#include <qwt_plot.h>
#include <qwt_plot_marker.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_picker.h>
#include <qwt_legend.h>
#include <qwt_text.h>
#include <qwt_text_label.h>
#include <qwt_math.h>
#include <qwt_symbol.h>
#include <QLabel>
#include <QLineEdit>
#include <QDateEdit>
#include <QRadioButton>
#include <QPushButton>

#include "Result.h"

namespace Ui {
class CustomQwtPlot;
}

class CustomQwtPlot : public QWidget
{
    Q_OBJECT

public:
    explicit CustomQwtPlot(QWidget *parent = 0);
    ~CustomQwtPlot();

public:
    Ui::CustomQwtPlot *ui;

    QwtPlot *getChart();
    QRadioButton* IfCaculate;
    QRadioButton* IfCustum;
    QLabel* txtAvg;
    QLabel* txtSd;
    QLabel* txtCV;
    QLabel* txt6sigma;

    QLineEdit* inputCustAvg;
    QLineEdit* inputCustSD;
    QLabel* txtCustCV;
    QLabel* txtCust6sigma;
    QDateEdit* inputStartDate;
    QDateEdit* inputEndDate;
    QLineEdit* txtN;
    QWidget* widget_4;
    QPushButton* btnCaculate;
    QPushButton* btnInit;

    void SetTitle(QString str);

    void SetFooter(QString str);

private:
    void DrawLjChart(QwtPlot*chart, int level, double avg, double s, double min, double max, QVector<Result> data);

//    void CheckData();

private slots:

    void on_btnDataTable_clicked();

public:
    QString current_projectId;
    int current_level;

    QVector<Result> m_data;

    QString m_currentRule;

    QDate m_startDate;
    QDate m_endDate;

    bool m_bAllShow;

};

#endif // CUSTOMQWTPLOT_H
