#ifndef ANALYZERULE_H
#define ANALYZERULE_H

#include <QDialog>
#include <QListWidget>
#include <QTreeWidget>
#include "Model/Result.h"
#include "Model/Project.h"

namespace Ui {
class AnalyzeRule;
}


class QwtPlot;

class AnalyzeRule : public QDialog
{
    Q_OBJECT
    
public:
    explicit AnalyzeRule(QWidget *parent = 0);
    ~AnalyzeRule();

    void InitProjects();
    
private slots:
    void on_inputKeyword_textChanged(const QString &arg1);

    void on_projectList_itemDoubleClicked(QListWidgetItem *item);

    void on_btnCancel_clicked();

    void on_checkBox_stateChanged();

    void on_btnSetRule_clicked();

    void on_inputTea_textChanged(const QString &arg1);

    void on_inputBias_textChanged(const QString &arg1);

    void on_inputCV_textChanged(const QString &arg1);

    void on_btnAddRule_clicked();

    void on_listWidget_doubleClicked(const QModelIndex &index);

    void on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column);

    void on_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);

    void DrawProjectChart();

private:
    Ui::AnalyzeRule *ui;

    QObjectList list;

    Project currentProject;
    QString currentTypeId;

    void InitRules();
    void DrawFuncChart(QwtPlot*chart, int type, QVector< QVector<Result> > allData, QVector< QVector<Result> > allData5090);
    void DrawOpChart(QwtPlot*chart, int type, QVector< QVector<Result> > allData, QVector<double> cvList, QVector<double> biasList, QVector<QString> nameList);
    void ShowProjectResult();

    bool needDisplay;

    int xCount;
    int testDataCount;

    QVector< QVector<Result> > results_se1;
    QVector< QVector<Result> > results_se2;
    QVector< QVector<Result> > results_se3;
    QVector< QVector<Result> > results_se4;
    QVector< QVector<Result> > results_se5;
    QVector< QVector<Result> > results_se6;


    QVector< QVector<Result> > results_re1;
    QVector< QVector<Result> > results_re2;
    QVector< QVector<Result> > results_re3;
    QVector< QVector<Result> > results_re4;
    QVector< QVector<Result> > results_re5;
    QVector< QVector<Result> > results_re6;
};

#endif // ANALYZERULE_H
