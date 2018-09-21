#ifndef EVALUATIONPARAMETER_H
#define EVALUATIONPARAMETER_H

#include <QWidget>
#include <QLineEdit>

namespace Ui {
class EvaluationParameter;
}

class EvaluationParameter : public QWidget
{
    Q_OBJECT

public:
    explicit EvaluationParameter(QWidget *parent = 0);
    ~EvaluationParameter();

    double Tea();
    double Bias();
    double Cv();
    double Sigma();

    void setTea(double tea);
    void setBias(double bias);
    void setCv(double cv);
    void setSigma(double sigma);

    void setTea(QString tea);
    void setBias(QString bias);
    void setCv(QString cv);
    void setSigma(QString sigma);

    void calculate();

Q_SIGNALS:
    void textChanged();

protected Q_SLOTS:

private slots:
    void on_inputTea_textChanged(const QString &arg1);

    void on_inputBias_textChanged(const QString &arg1);

    void on_inputCV_textChanged(const QString &arg1);

private:
    Ui::EvaluationParameter *ui;

};

#endif // EVALUATIONPARAMETER_H
