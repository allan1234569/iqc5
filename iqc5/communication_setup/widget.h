#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>


namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    void init();

private slots:

    void on_pushButtonEnsure_clicked();

    void on_pushButtonApply_clicked();

    void on_pushButtonCancel_clicked();

    void on_radioButtonSerialPortComm_clicked();

    void on_radioButtonNetComm_clicked();

    void on_comboBoxComPort_currentTextChanged(const QString &arg1);

    void on_comboBoxBaudRate_currentTextChanged(const QString &arg1);

    void on_comboBoxDataBits_currentTextChanged(const QString &arg1);

    void on_comboBoxStopBits_currentTextChanged(const QString &arg1);

    void on_comboBoxParity_currentIndexChanged(int index);

    void on_comboBoxCommMode_currentIndexChanged(int index);

    void on_comboBoxRecvBufferSize_currentTextChanged(const QString &arg1);

    void on_lineEditLocalPort_textChanged(const QString &arg1);

    void on_lineEditRemoteIp_textChanged(const QString &arg1);

    void on_lineEditRemotePort_textChanged(const QString &arg1);

    void on_comboBoxTimer_currentTextChanged(const QString &arg1);

    void slt_on_timeout();

private:
    void save();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
