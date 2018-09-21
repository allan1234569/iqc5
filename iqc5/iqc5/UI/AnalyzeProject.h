#ifndef ANALYZEPROJECT_H
#define ANALYZEPROJECT_H

#include <QMainWindow>
#include <QListWidget>
#include <QTreeWidget>
#include "Model/Result.h"
#include "Model/Project.h"
#include "UI/PopBox.h"
#include "CustomQwtPlot.h"
#include <QThread>

#ifdef Q_OS_WIN
#include <windows.h>
#endif


class AProcess : public QThread
{
    Q_OBJECT
public:
    explicit AProcess(QObject *parent = 0);
    ~AProcess();

    void setProgram(const QString &path);

signals:


public slots:



    // QThread interfacecx
protected:
    void run();

private:
    QString m_sProgram;
};

class QwtPlot;
class QwtPlotPicker;

namespace Ui {
class AnalyzeProject;
}

class AnalyzeProject : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit AnalyzeProject(QWidget *parent = 0);
    ~AnalyzeProject();

    void InitProjects();

    void SetMode(int mode);

    CustomQwtPlot* getChart();

    int mode;
    
private slots:
    void on_btnCancel_clicked();

    void on_inputKeyword_textChanged(const QString &arg1);

    void on_checkBox_stateChanged();

    void on_btnAddRule_clicked();

    void on_listWidget_doubleClicked(const QModelIndex &index);



    void on_btnExport_clicked();

    void on_btnExportByType_clicked();

//    void on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column);

    void on_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);

    void on_tabWidget_currentChanged(int index);

    void on_btnPrint_clicked();

    void on_btnDataTable_clicked();

    void on_inputCustAvg_textChanged(const QString &arg1);

    void on_inputCustSD_textChanged(const QString &arg1);

    void on_inputStartDate_Changed(const QDate &date);

    void on_inputEndDate_Changed(const QDate &date);

    void on_IfCaculate_toggled(bool checked);

    void on_btnImport_clicked();

    void on_btnCaculate_clicked();

    void on_btnInit_clicked();

    void on_cbkShowAll_toggled(bool checked);

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_listWidget_itemSelectionChanged();

    void on_dataImport_clicked();

private:
    Ui::AnalyzeProject *ui;

    Project currentProject;

    int currentIndex;

    QwtPlotPicker *m_picker;

    PopBox *pop;

    QObjectList list;

    QListWidgetItem *lastListWidgetItem;

    void InitRules();
    void DrawLjChart();
    void DrawLjChart(QwtPlot*chart, int level, double avg, double s, double min, double max, QVector<Result> data);

    void DrawBarChart();
    void DrawBarChart(QwtPlot*chart, int level, double avg, double s, double min, double max, QVector<QwtOHLCSample> data);

    void DrawZChart();

    void DrawTargetChart();
    void DrawTargetChart(QwtPlot*chart, int level, double avg, double s, double min, double max, QVector<Result> data);

    void ShowTable(QString title, int rowCount, QVector< QVector<Result> > allData);
    void ShowProjectResult();
    void DrawProjectChart();
    void ChangeChart(int currentIndex);
    /**
     * @brief CheckData 数据有效性检查
     */
    void CheckData();

    /**
     * @brief InitCheckData 初始化或累积计算时的数据有效性检查
     * @param timeSplitString 时间,  格式：起始日期,结束日期   如 2016-01-01,2016-02-01
     */
    bool InitCheckData(QVector<QVector<Result> > av_data, QString timeSplitString = "");

    bool eventFilter(QObject *object, QEvent *e);

    void select(QwtPlot* chart, const QPoint &pos);

//    wchar_t *char2wchar(char *src);

#ifdef Q_OS_WIN

    /**
     * @brief SendCommand
     * @param hw
     * @param command
     */
    void SendCommand(const char *uft8_handle);

#endif
    bool needDisplay;
    bool showMsgBox;

    QVector<QVector<Result> > allData;

    CustomQwtPlot* chart_z;

};

#endif // ANALYZEPROJECT_H
