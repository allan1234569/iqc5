#include "EvaluationParameter.h"
#include "ui_EvaluationParameter.h"

#include <QRegExp>

EvaluationParameter::EvaluationParameter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EvaluationParameter)
{
    ui->setupUi(this);

    QRegExp regExp("[0-9]+(.[0-9]{1,2})?$");
    ui->inputTea->setValidator(new QRegExpValidator(regExp,this));
    ui->inputBias->setValidator(new QRegExpValidator(regExp,this));
    ui->inputCV->setValidator(new QRegExpValidator(regExp,this));
}

EvaluationParameter::~EvaluationParameter()
{
    delete ui;
}

double EvaluationParameter::Tea()
{
    return ui->inputTea->text().toDouble();
}

double EvaluationParameter::Bias()
{
    return ui->inputBias->text().toDouble();
}

double EvaluationParameter::Cv()
{
    return ui->inputCV->text().toDouble();
}

double EvaluationParameter::Sigma()
{
    return ui->inputSigma->text().toDouble();
}

void EvaluationParameter::setTea(double tea)
{
    ui->inputTea->setText(QString::number(tea));
}

void EvaluationParameter::setBias(double bias)
{
    ui->inputBias->setText(QString::number(bias));
}

void EvaluationParameter::setCv(double cv)
{
    ui->inputCV->setText(QString::number(cv));
}

void EvaluationParameter::setSigma(double sigma)
{
    ui->inputSigma->setText(QString::number(sigma,'f',2));
}

void EvaluationParameter::setTea(QString tea)
{
    ui->inputTea->setText(QString::number(tea.toDouble(),'f',2));
}

void EvaluationParameter::setBias(QString bias)
{
    ui->inputBias->setText(QString::number(bias.toDouble(),'f',2));
}

void EvaluationParameter::setCv(QString cv)
{
    ui->inputCV->setText(QString::number(cv.toDouble(),'f',2));
}

void EvaluationParameter::setSigma(QString sigma)
{
    ui->inputSigma->setText(QString::number(sigma.toDouble(),'f',2));
}

void EvaluationParameter::calculate()
{
    emit textChanged();

    if(ui->inputTea->text().isEmpty() || ui->inputBias->text().isEmpty() || ui->inputCV->text().isEmpty())
    {
        setSigma("");
        return;
    }

    if(!ui->inputTea->text().isEmpty() && !ui->inputBias->text().isEmpty() && !ui->inputCV->text().isEmpty())
    {
        if(ui->inputCV->text().toDouble() == 0.0)
        {
            setSigma("");
        }
        else
        {
            double sigma = (ui->inputTea->text().toDouble() - ui->inputBias->text().toDouble()) / ui->inputCV->text().toDouble();
            setSigma(sigma);
        }
    }
}

void EvaluationParameter::on_inputTea_textChanged(const QString &arg1)
{
    calculate();
}

void EvaluationParameter::on_inputBias_textChanged(const QString &arg1)
{
    calculate();
}

void EvaluationParameter::on_inputCV_textChanged(const QString &arg1)
{
    calculate();
}
