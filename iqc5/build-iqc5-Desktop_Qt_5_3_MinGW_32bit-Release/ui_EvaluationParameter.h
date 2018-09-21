/********************************************************************************
** Form generated from reading UI file 'EvaluationParameter.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EVALUATIONPARAMETER_H
#define UI_EVALUATIONPARAMETER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EvaluationParameter
{
public:
    QLabel *label_8;
    QLabel *label_6;
    QLineEdit *inputBias;
    QLabel *label_7;
    QLineEdit *inputTea;
    QLineEdit *inputCV;
    QLabel *label;
    QLineEdit *inputSigma;

    void setupUi(QWidget *EvaluationParameter)
    {
        if (EvaluationParameter->objectName().isEmpty())
            EvaluationParameter->setObjectName(QStringLiteral("EvaluationParameter"));
        EvaluationParameter->resize(536, 71);
        label_8 = new QLabel(EvaluationParameter);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(280, 10, 111, 20));
        label_8->setAlignment(Qt::AlignCenter);
        label_6 = new QLabel(EvaluationParameter);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(20, 10, 111, 20));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy);
        label_6->setAlignment(Qt::AlignCenter);
        inputBias = new QLineEdit(EvaluationParameter);
        inputBias->setObjectName(QStringLiteral("inputBias"));
        inputBias->setGeometry(QRect(150, 40, 113, 20));
        label_7 = new QLabel(EvaluationParameter);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(150, 10, 111, 20));
        label_7->setAlignment(Qt::AlignCenter);
        inputTea = new QLineEdit(EvaluationParameter);
        inputTea->setObjectName(QStringLiteral("inputTea"));
        inputTea->setGeometry(QRect(20, 40, 113, 20));
        inputCV = new QLineEdit(EvaluationParameter);
        inputCV->setObjectName(QStringLiteral("inputCV"));
        inputCV->setGeometry(QRect(280, 40, 113, 20));
        label = new QLabel(EvaluationParameter);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(410, 10, 110, 20));
        label->setAlignment(Qt::AlignCenter);
        inputSigma = new QLineEdit(EvaluationParameter);
        inputSigma->setObjectName(QStringLiteral("inputSigma"));
        inputSigma->setGeometry(QRect(410, 40, 113, 20));
        inputSigma->setReadOnly(true);
        QWidget::setTabOrder(inputTea, inputBias);
        QWidget::setTabOrder(inputBias, inputCV);
        QWidget::setTabOrder(inputCV, inputSigma);

        retranslateUi(EvaluationParameter);

        QMetaObject::connectSlotsByName(EvaluationParameter);
    } // setupUi

    void retranslateUi(QWidget *EvaluationParameter)
    {
        EvaluationParameter->setWindowTitle(QApplication::translate("EvaluationParameter", "Form", 0));
        label_8->setText(QApplication::translate("EvaluationParameter", "\345\205\201\350\256\270\344\270\215\347\262\276\347\241\256\345\272\246(CV)", 0));
        label_6->setText(QApplication::translate("EvaluationParameter", "\345\205\201\350\256\270\346\200\273\350\257\257\345\267\256(TEa)", 0));
        inputBias->setText(QString());
        label_7->setText(QApplication::translate("EvaluationParameter", "\345\205\201\350\256\270\345\201\217\345\200\232(Bias)", 0));
        inputTea->setText(QString());
        inputCV->setText(QString());
        label->setText(QApplication::translate("EvaluationParameter", "\317\203\345\200\274", 0));
    } // retranslateUi

};

namespace Ui {
    class EvaluationParameter: public Ui_EvaluationParameter {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EVALUATIONPARAMETER_H
