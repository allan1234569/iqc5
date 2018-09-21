#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QtitanRibbon.h>

#ifdef QT_NO_DEBUG
namespace Qtitan
{
    class WidgetGalleryItems;
    class OfficeWidgetGallery;
}
#endif

#ifdef QT_NO_DEBUG
class MainWindow : public Qtitan::RibbonMainWindow
#else
class MainWindow : public QMainWindow
#endif
{
    Q_OBJECT

public:

    static bool canOpen;
    explicit MainWindow(QWidget *parent = NULL);
    virtual ~MainWindow();

private:
#ifdef QT_NO_DEBUG
    void createOptions();
    void createRibbon();

    Qtitan::RibbonStyle* m_ribbonStyle;
#else
    void careteMenuBar();
#endif

Q_SIGNALS:
    void close();


protected Q_SLOTS:

#ifdef QT_NO_DEBUG
    void options(QAction* action);
#endif

    void newProject();
    void openProject();
    void InputDataBatch();
    void FuncNewProjectBatch();

    void importProject();
    void importConfig();
    void chooseMethod();
    void showLj();
    void showZ();
    void showBar();
    void showTarget();
    void showFuncChart();
    void showFuncChart1();
    void showCircle();

    void manageMaterial();
    void manageReagent();
    void manageTestType();
    void manageMethod();
    void manageDevice();
    void manageDataImport();

    void manageMaterialBatch();
    void manageReagentBatch();
    void manageMaterialTestType();
    void manageReagentTestType();
    void manageMethodTestType();
    void newMaterialBatch();
    void newReagentBatch();


    /***
     * 性能验证
     */
    void showPrecisionTest();//精密度验证
    void showAccuracyTest();//正确度验证
    void showMeasurementIntervalTest();//测量区间验证
    void showReferenceIntervalTest();//参考区间验证

    /***
     * 方法确认
     */
    void ShowSensitivityAnalyze();


    // QWidget interface
protected:
    void closeEvent(QCloseEvent *e);
};

#endif // MAINWINDOW_H
