#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

protected:
    void changeEvent(QEvent *e);

    /**
     * @brief get_mac   获取机器的Mac地址
     * @return
     */
    QStringList get_mac();

    void getcpuid(unsigned int CPUInfo[4], unsigned int InfoType);

    void getcpuidex(unsigned int CPUInfo[4], unsigned int InfoType, unsigned int ECXValue);

    QString get_cpuId();

    QString getMachineCode();

    QString calAccreditCode(QString machineCode);
private slots:
    void on_BtnQuit_clicked();
    void on_BtnGenerate_clicked();
    void on_MachineCode_LineEdit_textChanged(const QString &arg1);
    void on_AccreditCode_LineEdit_textChanged(const QString &arg1);
};

#endif // MAINWINDOW_H
