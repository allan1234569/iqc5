#ifndef PV_PRECISION_H
#define PV_PRECISION_H

#include <QDialog>
#include <QListWidget>
#include <QLineEdit>
#include <QDateTimeEdit>
#include <QComboBox>
#include <QVector>
#include <QTextBrowser>
#include <Pv_TextBrowser.h>
#include <QTableWidget>
#include "Common/Axis.h"

//Model
#include "Precision.h"

#define DISPLAY_ONE

namespace Ui {
class Pv_Precision;
}

class Pv_Precision : public QDialog
{
    Q_OBJECT

    enum TYPE{
        EP5,
        EP15,
        WESTGARD,
    };
    enum LEVEL{
        ONE,
        TWO,
        THREE
    };

public:
    explicit Pv_Precision(QWidget *parent = 0);
    void Init();

    void showEp5();
    void showEp5Table(QTableWidget *widget);


    void showWestgard();

    void showEp15();

    //临时示例
    void show_ep5_samples();
    void show_westgard_samples();
    void show_ep15_samples();

    /**
     * @brief getOutliersIndex  得到离群值的坐标
     * @param level1Map         浓度水平1的坐标位置
     * @param level2Map         浓度水平2的坐标位置
     */
    void getOutliersIndex(QMap<int, QMap<QString, QString> > level1Map, QMap<int, QMap<QString, QString> > level2Map, QVector<Axis<int> > &vec);

    QString toString(double val);

    QString GenerateReport(TYPE type);

    QString readFile(QString &filename);

    QString htmlString(QString replaceStr, int length = 0);

    QString ep5Html;
    QString westgardHtml;
    QString ep15Html;

    ~Pv_Precision();

private:
    Ui::Pv_Precision *ui;

private slots:
    //ep5方案
    void on_ep5_BtnExperimentalRequirements_clicked();
    void on_ep5_BtnCommit_clicked();
    void on_ep5_BtnOutputReport_clicked();
    void on_ep5_L2_clicked();
    void on_ep5_L3_clicked();

    void on_ep5_instrument_textChanged(const QString str);
    void on_ep5_sample_textChanged(const QString str);
    void on_ep5_ReagenBatchNo_textChanged(const QString str);
    void on_ep5_CPBatchNo_textChanged(const QString str);
    void on_ep5_Analyte_textChanged(const QString str);

    //Westgard方案
    void on_Westgard_BtnExperimentalRequirements_clicked();
    void on_Westgard_BtnCommit_clicked();
    void on_Westgard_BtnOutputReport_clicked();
    void on_Westgard_L2_clicked();
    void on_Westgard_L3_clicked();

    void on_Westgard_Instrument_textChanged(const QString str);
    void on_Westgard_Sample_textChanged(const QString str);
    void on_Westgard_ReagenBatchNo_textChanged(const QString str);
    void on_Westgard_CPBatchNo_textChanged(const QString str);
    void on_Westgard_Analyte_textChanged(const QString str);

    void Westgard_AddColumns(QString label);
    void Westgard_RemoveColumns();

    //ep15方案
    void on_ep15_BtnExperimentalRequirements_clicked();
    void on_ep15_BtnCommit_clicked();
    void on_ep15_BtnOutputReport_clicked();
    void on_ep15_L2_clicked();
    void on_ep15_L3_clicked();

    void on_ep15_Instrument_textChanged(const QString str);
    void on_ep15_ReagenBatchNo_textChanged(const QString str);
    void on_ep15_CPBatchNo_textChanged(const QString str);
    void on_ep15_AnalysisProgram_textChanged(const QString str);

    void ep15_AddRows(QTableWidget *tableWidget, QString label);
    void ep15_RemoveRows(QTableWidget *tableWidget);


    void on_listWidget_clicked(const QModelIndex);

    void showExperimentalRequirements(QString &filename);

    void _textChanged(QString str);

    void SlotItemClicked(QTableWidgetItem *item);

protected:
    void keyPressEvent (QKeyEvent * keyevent);
    void closeEvent(QCloseEvent* event);
    void mousePressEvent(QMouseEvent *event);
    void timerEvent(QTimerEvent *event);
    void contextMenuEvent(QContextMenuEvent *e);

private:
    QString GenerateEp5Html();

    /**
     * @brief ep5Level1Html
     * @param html          需要修改的Html字符串
     * @return              返回报告结果，true为可以接受，false为不能接受
     */
    bool ep5Level1Html(QString &html);
    bool ep5Level2Html(QString &html);
    bool ep5Level3Html(QString &html);

    QString GenerateEpWeatgardHtml();

    QString GenerateEp15Html();


    bool Check_EP5_tables(LEVEL level);
    bool Check_EP5_table_ByName(QTableWidget* widget, int tableIndex);
    void Commit_Ep5_Table1();
    void Commit_Ep5_Table2();
    void Commit_Ep5_Table3();

    void Commit_Ep15_L1();
    void Commit_Ep15_L2();
    void Commit_Ep15_L3();

    bool check(QString prefix, QString filter = "");

    /**
     * @brief setStyle
     * @param method            方案，当method给"All"或给""时，对所有输入对话框有效，否则对指定的objectName的对话框有效
     * @param lineEditStyle     QLineEdit的CSS样式
     * @param dateEditStyle     QDateEdit的CSS样式
     * @param fConnent          为真时，建立信号与槽的连接，默认不需要
     */
    void setStyle(const QString method, const QString &lineEditStyle, const QString &dateEditStyle, bool fConnent = false);

    void ShowMenu();

    void showWarning(QString text);

    void showInformation(QString text);

public:



private:
    QListWidget *listWidget;
    QLineEdit *lineEdit;
    Pv_TextBrowser *browser;
    QVector< Axis<int> > outliersAxisVec1;//分别对应三张表的离群值的坐标
    QVector< Axis<int> > outliersAxisVec2;
    QVector< Axis<int> > outliersAxisVec3;
    int count;
    int timeId;
    PrecisionEp5 precision1;    //分别对应三张表
    PrecisionEp5 precision2;
    PrecisionEp5 precision3;

    PrecisionWestgard westgardInbatch;//批内
    PrecisionWestgard westgardBatchs; //批间

    PrecisionEp15 ep15Precision1;
    PrecisionEp15 ep15Precision2;
    PrecisionEp15 ep15Precision3;

    LEVEL ep5Level;
    LEVEL ep15Level;
    LEVEL westgardLevel;

    QList<QLineEdit*> lineEditPointerList;

    QString defaultStyle;
    QString warningStyle;
    QString dateEditStyle;
    int page;
};

#endif // PV_PRECISION_H
