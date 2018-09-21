#ifndef CHARTVIEW_H
#define CHARTVIEW_H

#include <QWidget>
#include "Model/Result.h"
#include "Model/Project.h"
#include "UI/PopBox.h"
#include <qwt_plot.h>
#include <qwt_plot_marker.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_picker.h>
#include <qwt_plot_panner.h>
#include <qwt_legend.h>
#include <qwt_text.h>
#include <qwt_text_label.h>
#include <qwt_math.h>
#include <qwt_symbol.h>
#include <qwt_scale_widget.h>
#include <qwt_plot_layout.h>
#include <qwt_plot_canvas.h>
#include "CustomQwtPlot.h"
#include <QMessageBox>

namespace Ui {
class ChartView;
}

class ChartView : public QWidget
{
    Q_OBJECT
    
public:

    QVector<Project> projectList;

    int index;
    int mode;
    PopBox *pop;
    bool showMsgBox;
    bool needRefresh;
    void initRules(QString testTypeId, QString currentRule);


    //QVector< QVector<Result> > allData;

    explicit ChartView(QWidget *parent = 0);
    void DrawLjChart(QVector<Project> projects, int index, QString currentRule, double avg[], double sd[], bool IfCaculate);
    void DrawLjChart(QwtPlot*chart, int level, double avg, double s, double min, double max, QVector<Result> data);
    void DrawZChart(QVector<Project> projects, int index, QString currentRule, double avg[], double sd[], bool IfCaculate);
    void keyPressEvent (QKeyEvent * keyevent);
    bool eventFilter(QObject *object, QEvent *e);
    void select(QwtPlot* chart, const QPoint &pos);
    ~ChartView();

    void CheckData(QVector< QVector<Result> > &allData);
    void ChangeChart();

    CustomQwtPlot *getChart();

private slots:
    void on_inputCustAvg_textChanged(const QString &arg1);

    void on_inputCustSD_textChanged(const QString &arg1);

    void on_inputStartDate_Changed(const QDate &date);

    void on_inputEndDate_Changed(const QDate &date);

    void on_IfCaculate_toggled(bool checked);

    void on_btnCaculate_clicked();

    void on_btnInit_clicked();

    void on_cbkShowAll_toggled(bool checked);
    
    void on_listWidget_currentIndexChanged(int i);

    void on_btnAreaData_clicked();

private:
    Ui::ChartView *ui;

};

#endif // CHARTVIEW_H
