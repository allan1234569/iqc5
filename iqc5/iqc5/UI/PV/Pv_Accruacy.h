#ifndef PV_ACCRUACY_H
#define PV_ACCRUACY_H

#include <QDialog>
#include <QLineEdit>
#include <QListWidget>
#include <QPixmap>
#include "Accruacy.h"
#include "Pv_ExcursionChart.h"
#include "Pv_TextBrowser.h"

#include <QPrinter>

namespace Ui {
class Pv_Accruacy;
}

class Pv_Accruacy : public QDialog
{
    Q_OBJECT

public:
    explicit Pv_Accruacy(QWidget *parent = 0);
    void Init();
    void showEp9Table();
    void showEp15Table();

    void show_patient_samples();//示例患者样本
    void show_reference_samples();//示例参考物质
    ~Pv_Accruacy();

private:
    Ui::Pv_Accruacy *ui;

private slots:
    void on_ep9_BtnPlot_clicked();
    void on_ep9_BtnExperimentalRequirements_clicked();

    void on_ep15_BtnCommit_clicked();
    void on_ep15_BtnPrint_clicked();
    void on_ep15_BtnExcursionChart_clicked();
    void on_ep15_BtnExperimentalRequirements_clicked();

    void on_ep15_BtnCommit_2_clicked();
    void on_ep15_BtnExperimentalRequirements_2_clicked();

    //ep9方案
    void on_ep9_InstrumentX_textChanged();
    void on_ep9_InstrumentY_textChanged();

    void on_ep9_XMethod_textChanged();
    void on_ep9_YMethod_textChanged();
//    void on_ep9_XReferenceRange_textChanged();
//    void on_ep9_XDetectionRange_textChanged();

    //ep15使用患者样本方案
    void on_ep15_Device_textChanged();
    void on_ep15_analysisProgram_textChanged();
    void on_ep15_ReagenBatch_textChanged(const QString &arg1);
    void on_ep15_CalibratorBatch_textChanged();

    //ep15使用参考物质方案
    void on_ep15_Device_2_textChanged();
    void on_ep15_analysisProgram_2_textChanged();
    void on_ep15_ReagenBatch_2_textChanged();
    void on_ep15_CalibratorBatch_2_textChanged();
    void on_ep15_Concentration_2_textChanged();

    void showExperimentalRequirements(QString &filename);

protected:
    void keyPressEvent (QKeyEvent * keyevent);
    void closeEvent(QCloseEvent* event);
    void mousePressEvent(QMouseEvent *event);

private:
    QLineEdit *lineEdit;
    QListWidget *listWidget;
    Pv_TextBrowser *browser;
    Accruacy_PatientSample accruacyPatient;
    Accruacy_ReferenceMaterial accruacyMaterial;
    Pv_ExcursionChart *excursionChart;

    QPixmap image;
};

#endif // PV_ACCRUACY_H
