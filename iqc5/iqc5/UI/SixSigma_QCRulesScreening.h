#ifndef SIXSIGMA_QCRULESSCREENING_H
#define SIXSIGMA_QCRULESSCREENING_H

#include <QMainWindow>
#include <QTreeWidgetItem>
#include <QMap>

namespace Ui {
class SixSigma_QCRulesScreening;
}

class SixSigma_QCRulesScreening : public QMainWindow
{
    Q_OBJECT

public:
    explicit SixSigma_QCRulesScreening(QWidget *parent = 0);
    ~SixSigma_QCRulesScreening();

    void InitProjects();

    void InitPlot();

    /**
     * @brief drawMedicalDecisionChart  画方法评价决策图
     * @param Tea
     * @param Bias
     * @param Cv
     */
    void drawMedicalDecisionChart(double Tea, double Bias, double Cv);

    /**
     * @brief draw_100PercentMedicalDecisionChart   画标化100%时的方法评价决策图
     */
    void draw_100PercentMedicalDecisionChart();

    void addWidgetToStackedWidget(QWidget *widget, int index);

    void saveParams();

    void getparams();

private slots:
    void on_input_keyword_textChanged(const QString &arg1);

    void on_treeWidget_itemSelectionChanged();

    void on_stackedWidget_currentChanged(int arg1);

    void slt_hasParamChanged();

    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);

private:
    Ui::SixSigma_QCRulesScreening *ui;

    QMap<QString, int> pro2widget_Map;
    QMap<QString, QString> projectList;
    QMap<QString, QString> projectParamList;

    bool m_bParamChanged;

    bool m_bNeedShow;

    // QWidget interface
protected:
    void closeEvent(QCloseEvent *e);
};

#endif // SIXSIGMA_QCRULESSCREENING_H
