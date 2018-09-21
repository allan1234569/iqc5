#ifndef CIRCLE_H
#define CIRCLE_H

#include <QDialog>
#include <QListWidget>
#include <QComboBox>
#include <QTreeWidgetItem>
#include "Model/Result.h"
#include "Model/Project.h"
#include "CircleView.h"

class QwtPlot;
class QwtPlotPicker;


namespace Ui {
class Circle;
}

class Circle : public QDialog
{
    Q_OBJECT

public:
    CircleView *c;

public:
    explicit Circle(QWidget *parent = 0);
    ~Circle();

private slots:
    void on_btnCancel_clicked();

    void on_inputKeyword_textChanged(const QString &arg1);

    void on_checkBox_stateChanged();

    void on_btnAddRule_clicked();

    void on_listWidget_clicked(const QModelIndex &index);

    void on_listWidget_doubleClicked(const QModelIndex &index);

    void on_add_currentIndexChanged(const QString &arg1);

    void on_btnCaculate_clicked();

    void on_btnImport_clicked();

    void on_listWidget_currentIndexChanged(int index);

    void on_btnAreaData_clicked();

    void DrawTable();

    void on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column);

    void on_pushButton_clicked();

private:
    Ui::Circle *ui;

    QString currentDate;
    QVector< QVector< QVector<Result> > > allData;
    QVector< QVector< QVector<Result> > > oneDayData;
    QVector< QVector<Result> > allAreaData;

    QwtPlotPicker *m_picker;

    void InitProjects();
    void InitRules();
    void GenerateData20();
    void ShowProjectResult();
    void DrawCircleChart();
    void DrawZChart();
    void AddToAllDate(QString categoryId, QString date);
    void AddToDayDate(QString categoryId, QString date);

    bool eventFilter(QObject *object, QEvent *e);

    void select(QwtPlot* chart, const QPoint &pos);

    void CheckData();

    void InitTree();

    bool needDisplay;

    double oldAdd;//偏移量
};

#endif // CIRCLE_H
