/********************************************************************************
** Form generated from reading UI file 'Pv_AccuracyPlot.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PV_ACCURACYPLOT_H
#define UI_PV_ACCURACYPLOT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include "qwt_plot.h"

QT_BEGIN_NAMESPACE

class Ui_Pv_AccuracyPlot
{
public:
    QVBoxLayout *verticalLayout_2;
    QGridLayout *gridLayout;
    QLineEdit *AcPlot_YMethod;
    QLineEdit *AcPlot_XDetectionRange;
    QLineEdit *AcPlot_InstrumentX;
    QLabel *label_5;
    QSpacerItem *horizontalSpacer;
    QLabel *label_3;
    QLabel *label_4;
    QLineEdit *AcPlot_InstrumentY;
    QLabel *label_7;
    QLineEdit *AcPlot_XMethod;
    QLabel *label_2;
    QLabel *label_8;
    QLineEdit *AcPlot_XReferenceRange;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_6;
    QLabel *label;
    QLineEdit *AcPlot_YReferenceRange;
    QLineEdit *AcPlot_YDetectionRange;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label_26;
    QwtPlot *qwtPlot;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_27;
    QwtPlot *qwtPlot_2;
    QGridLayout *gridLayout_2;
    QLabel *label_20;
    QLabel *label_17;
    QLabel *label_18;
    QLabel *label_19;
    QLineEdit *AcPlot_BiasValue;
    QLineEdit *AcPlot_BiasInterval;
    QLabel *label_14;
    QLabel *label_15;
    QSpacerItem *horizontalSpacer_8;
    QLineEdit *AcPolt_RegressionEquation;
    QLineEdit *lineEdit_9;
    QLineEdit *AcPlot_RelatedCoefficient;
    QLineEdit *AcPlot_MedicalDecideLevel;
    QLineEdit *AcPlot_ExpectedValue;
    QLineEdit *lineEdit_13;
    QLabel *label_9;
    QLabel *label_16;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_13;
    QSpacerItem *horizontalSpacer_7;
    QSpacerItem *horizontalSpacer_6;
    QSpacerItem *horizontalSpacer_9;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_3;
    QGridLayout *gridLayout_3;
    QSpacerItem *horizontalSpacer_4;
    QDateEdit *AcPlot_CalculateDate;
    QLabel *label_25;
    QPlainTextEdit *AcPlot_Annotation;
    QLabel *label_21;
    QLabel *label_22;
    QLabel *label_23;
    QLabel *label_24;
    QLineEdit *AcPlot_Technicina;
    QLineEdit *AcPlot_Auditor;
    QDateEdit *AcPlot_ApprovalDate;
    QSpacerItem *horizontalSpacer_5;

    void setupUi(QDialog *Pv_AccuracyPlot)
    {
        if (Pv_AccuracyPlot->objectName().isEmpty())
            Pv_AccuracyPlot->setObjectName(QStringLiteral("Pv_AccuracyPlot"));
        Pv_AccuracyPlot->resize(1046, 682);
        verticalLayout_2 = new QVBoxLayout(Pv_AccuracyPlot);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        AcPlot_YMethod = new QLineEdit(Pv_AccuracyPlot);
        AcPlot_YMethod->setObjectName(QStringLiteral("AcPlot_YMethod"));

        gridLayout->addWidget(AcPlot_YMethod, 1, 4, 1, 1);

        AcPlot_XDetectionRange = new QLineEdit(Pv_AccuracyPlot);
        AcPlot_XDetectionRange->setObjectName(QStringLiteral("AcPlot_XDetectionRange"));

        gridLayout->addWidget(AcPlot_XDetectionRange, 3, 1, 1, 1);

        AcPlot_InstrumentX = new QLineEdit(Pv_AccuracyPlot);
        AcPlot_InstrumentX->setObjectName(QStringLiteral("AcPlot_InstrumentX"));

        gridLayout->addWidget(AcPlot_InstrumentX, 0, 1, 1, 1);

        label_5 = new QLabel(Pv_AccuracyPlot);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 0, 3, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 2, 1, 1);

        label_3 = new QLabel(Pv_AccuracyPlot);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        label_4 = new QLabel(Pv_AccuracyPlot);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        AcPlot_InstrumentY = new QLineEdit(Pv_AccuracyPlot);
        AcPlot_InstrumentY->setObjectName(QStringLiteral("AcPlot_InstrumentY"));

        gridLayout->addWidget(AcPlot_InstrumentY, 0, 4, 1, 1);

        label_7 = new QLabel(Pv_AccuracyPlot);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout->addWidget(label_7, 2, 3, 1, 1);

        AcPlot_XMethod = new QLineEdit(Pv_AccuracyPlot);
        AcPlot_XMethod->setObjectName(QStringLiteral("AcPlot_XMethod"));

        gridLayout->addWidget(AcPlot_XMethod, 1, 1, 1, 1);

        label_2 = new QLabel(Pv_AccuracyPlot);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        label_8 = new QLabel(Pv_AccuracyPlot);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout->addWidget(label_8, 3, 3, 1, 1);

        AcPlot_XReferenceRange = new QLineEdit(Pv_AccuracyPlot);
        AcPlot_XReferenceRange->setObjectName(QStringLiteral("AcPlot_XReferenceRange"));

        gridLayout->addWidget(AcPlot_XReferenceRange, 2, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 5, 1, 1);

        label_6 = new QLabel(Pv_AccuracyPlot);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout->addWidget(label_6, 1, 3, 1, 1);

        label = new QLabel(Pv_AccuracyPlot);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        AcPlot_YReferenceRange = new QLineEdit(Pv_AccuracyPlot);
        AcPlot_YReferenceRange->setObjectName(QStringLiteral("AcPlot_YReferenceRange"));

        gridLayout->addWidget(AcPlot_YReferenceRange, 2, 4, 1, 1);

        AcPlot_YDetectionRange = new QLineEdit(Pv_AccuracyPlot);
        AcPlot_YDetectionRange->setObjectName(QStringLiteral("AcPlot_YDetectionRange"));

        gridLayout->addWidget(AcPlot_YDetectionRange, 3, 4, 1, 1);


        verticalLayout_2->addLayout(gridLayout);

        groupBox = new QGroupBox(Pv_AccuracyPlot);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        horizontalLayout_2 = new QHBoxLayout(groupBox);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label_26 = new QLabel(groupBox);
        label_26->setObjectName(QStringLiteral("label_26"));
        label_26->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_26);

        qwtPlot = new QwtPlot(groupBox);
        qwtPlot->setObjectName(QStringLiteral("qwtPlot"));

        verticalLayout->addWidget(qwtPlot);


        horizontalLayout_2->addLayout(verticalLayout);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label_27 = new QLabel(groupBox);
        label_27->setObjectName(QStringLiteral("label_27"));
        label_27->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(label_27);

        qwtPlot_2 = new QwtPlot(groupBox);
        qwtPlot_2->setObjectName(QStringLiteral("qwtPlot_2"));

        verticalLayout_3->addWidget(qwtPlot_2);


        horizontalLayout_2->addLayout(verticalLayout_3);


        verticalLayout_2->addWidget(groupBox);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label_20 = new QLabel(Pv_AccuracyPlot);
        label_20->setObjectName(QStringLiteral("label_20"));

        gridLayout_2->addWidget(label_20, 7, 1, 1, 1);

        label_17 = new QLabel(Pv_AccuracyPlot);
        label_17->setObjectName(QStringLiteral("label_17"));

        gridLayout_2->addWidget(label_17, 5, 0, 1, 1);

        label_18 = new QLabel(Pv_AccuracyPlot);
        label_18->setObjectName(QStringLiteral("label_18"));

        gridLayout_2->addWidget(label_18, 6, 0, 1, 1);

        label_19 = new QLabel(Pv_AccuracyPlot);
        label_19->setObjectName(QStringLiteral("label_19"));

        gridLayout_2->addWidget(label_19, 7, 0, 1, 1);

        AcPlot_BiasValue = new QLineEdit(Pv_AccuracyPlot);
        AcPlot_BiasValue->setObjectName(QStringLiteral("AcPlot_BiasValue"));

        gridLayout_2->addWidget(AcPlot_BiasValue, 5, 1, 1, 1);

        AcPlot_BiasInterval = new QLineEdit(Pv_AccuracyPlot);
        AcPlot_BiasInterval->setObjectName(QStringLiteral("AcPlot_BiasInterval"));

        gridLayout_2->addWidget(AcPlot_BiasInterval, 6, 1, 1, 1);

        label_14 = new QLabel(Pv_AccuracyPlot);
        label_14->setObjectName(QStringLiteral("label_14"));

        gridLayout_2->addWidget(label_14, 1, 3, 1, 1);

        label_15 = new QLabel(Pv_AccuracyPlot);
        label_15->setObjectName(QStringLiteral("label_15"));

        gridLayout_2->addWidget(label_15, 3, 3, 1, 1);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_8, 0, 7, 1, 1);

        AcPolt_RegressionEquation = new QLineEdit(Pv_AccuracyPlot);
        AcPolt_RegressionEquation->setObjectName(QStringLiteral("AcPolt_RegressionEquation"));

        gridLayout_2->addWidget(AcPolt_RegressionEquation, 0, 1, 1, 1);

        lineEdit_9 = new QLineEdit(Pv_AccuracyPlot);
        lineEdit_9->setObjectName(QStringLiteral("lineEdit_9"));

        gridLayout_2->addWidget(lineEdit_9, 0, 4, 1, 1);

        AcPlot_RelatedCoefficient = new QLineEdit(Pv_AccuracyPlot);
        AcPlot_RelatedCoefficient->setObjectName(QStringLiteral("AcPlot_RelatedCoefficient"));

        gridLayout_2->addWidget(AcPlot_RelatedCoefficient, 1, 1, 1, 1);

        AcPlot_MedicalDecideLevel = new QLineEdit(Pv_AccuracyPlot);
        AcPlot_MedicalDecideLevel->setObjectName(QStringLiteral("AcPlot_MedicalDecideLevel"));

        gridLayout_2->addWidget(AcPlot_MedicalDecideLevel, 2, 1, 1, 1);

        AcPlot_ExpectedValue = new QLineEdit(Pv_AccuracyPlot);
        AcPlot_ExpectedValue->setObjectName(QStringLiteral("AcPlot_ExpectedValue"));

        gridLayout_2->addWidget(AcPlot_ExpectedValue, 3, 1, 1, 1);

        lineEdit_13 = new QLineEdit(Pv_AccuracyPlot);
        lineEdit_13->setObjectName(QStringLiteral("lineEdit_13"));

        gridLayout_2->addWidget(lineEdit_13, 1, 4, 1, 1);

        label_9 = new QLabel(Pv_AccuracyPlot);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout_2->addWidget(label_9, 0, 0, 1, 1);

        label_16 = new QLabel(Pv_AccuracyPlot);
        label_16->setObjectName(QStringLiteral("label_16"));

        gridLayout_2->addWidget(label_16, 4, 0, 1, 1);

        pushButton = new QPushButton(Pv_AccuracyPlot);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout_2->addWidget(pushButton, 7, 5, 1, 1);

        pushButton_2 = new QPushButton(Pv_AccuracyPlot);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        gridLayout_2->addWidget(pushButton_2, 7, 7, 1, 1);

        label_10 = new QLabel(Pv_AccuracyPlot);
        label_10->setObjectName(QStringLiteral("label_10"));

        gridLayout_2->addWidget(label_10, 1, 0, 1, 1);

        label_11 = new QLabel(Pv_AccuracyPlot);
        label_11->setObjectName(QStringLiteral("label_11"));

        gridLayout_2->addWidget(label_11, 2, 0, 1, 1);

        label_12 = new QLabel(Pv_AccuracyPlot);
        label_12->setObjectName(QStringLiteral("label_12"));

        gridLayout_2->addWidget(label_12, 3, 0, 1, 1);

        label_13 = new QLabel(Pv_AccuracyPlot);
        label_13->setObjectName(QStringLiteral("label_13"));

        gridLayout_2->addWidget(label_13, 0, 3, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_7, 0, 5, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_6, 0, 2, 1, 1);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_9, 0, 6, 1, 1);

        gridLayout_2->setColumnStretch(0, 1);
        gridLayout_2->setColumnStretch(1, 2);
        gridLayout_2->setColumnStretch(2, 3);
        gridLayout_2->setColumnStretch(4, 2);
        gridLayout_2->setColumnStretch(5, 1);
        gridLayout_2->setColumnStretch(6, 1);

        verticalLayout_2->addLayout(gridLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);


        verticalLayout_2->addLayout(horizontalLayout);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_4, 0, 2, 1, 1);

        AcPlot_CalculateDate = new QDateEdit(Pv_AccuracyPlot);
        AcPlot_CalculateDate->setObjectName(QStringLiteral("AcPlot_CalculateDate"));
        AcPlot_CalculateDate->setCalendarPopup(true);

        gridLayout_3->addWidget(AcPlot_CalculateDate, 0, 4, 1, 1);

        label_25 = new QLabel(Pv_AccuracyPlot);
        label_25->setObjectName(QStringLiteral("label_25"));

        gridLayout_3->addWidget(label_25, 2, 0, 1, 1);

        AcPlot_Annotation = new QPlainTextEdit(Pv_AccuracyPlot);
        AcPlot_Annotation->setObjectName(QStringLiteral("AcPlot_Annotation"));
        AcPlot_Annotation->setMaximumSize(QSize(16777215, 40));

        gridLayout_3->addWidget(AcPlot_Annotation, 2, 1, 1, 4);

        label_21 = new QLabel(Pv_AccuracyPlot);
        label_21->setObjectName(QStringLiteral("label_21"));

        gridLayout_3->addWidget(label_21, 0, 0, 1, 1);

        label_22 = new QLabel(Pv_AccuracyPlot);
        label_22->setObjectName(QStringLiteral("label_22"));

        gridLayout_3->addWidget(label_22, 1, 0, 1, 1);

        label_23 = new QLabel(Pv_AccuracyPlot);
        label_23->setObjectName(QStringLiteral("label_23"));

        gridLayout_3->addWidget(label_23, 0, 3, 1, 1);

        label_24 = new QLabel(Pv_AccuracyPlot);
        label_24->setObjectName(QStringLiteral("label_24"));

        gridLayout_3->addWidget(label_24, 1, 3, 1, 1);

        AcPlot_Technicina = new QLineEdit(Pv_AccuracyPlot);
        AcPlot_Technicina->setObjectName(QStringLiteral("AcPlot_Technicina"));

        gridLayout_3->addWidget(AcPlot_Technicina, 0, 1, 1, 1);

        AcPlot_Auditor = new QLineEdit(Pv_AccuracyPlot);
        AcPlot_Auditor->setObjectName(QStringLiteral("AcPlot_Auditor"));

        gridLayout_3->addWidget(AcPlot_Auditor, 1, 1, 1, 1);

        AcPlot_ApprovalDate = new QDateEdit(Pv_AccuracyPlot);
        AcPlot_ApprovalDate->setObjectName(QStringLiteral("AcPlot_ApprovalDate"));
        AcPlot_ApprovalDate->setCalendarPopup(true);

        gridLayout_3->addWidget(AcPlot_ApprovalDate, 1, 4, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_5, 0, 5, 1, 1);

        gridLayout_3->setColumnStretch(1, 1);
        gridLayout_3->setColumnStretch(2, 3);
        gridLayout_3->setColumnStretch(4, 1);
        gridLayout_3->setColumnStretch(5, 3);

        verticalLayout_2->addLayout(gridLayout_3);

        verticalLayout_2->setStretch(1, 2);
        verticalLayout_2->setStretch(2, 1);

        retranslateUi(Pv_AccuracyPlot);

        QMetaObject::connectSlotsByName(Pv_AccuracyPlot);
    } // setupUi

    void retranslateUi(QDialog *Pv_AccuracyPlot)
    {
        Pv_AccuracyPlot->setWindowTitle(QApplication::translate("Pv_AccuracyPlot", "Dialog", 0));
        label_5->setText(QApplication::translate("Pv_AccuracyPlot", "\344\273\252\345\231\250\357\274\210Y\357\274\211\357\274\232", 0));
        label_3->setText(QApplication::translate("Pv_AccuracyPlot", "\345\217\202\350\200\203\350\214\203\345\233\264\357\274\232", 0));
        label_4->setText(QApplication::translate("Pv_AccuracyPlot", "\346\243\200\346\265\213\350\214\203\345\233\264\357\274\232", 0));
        label_7->setText(QApplication::translate("Pv_AccuracyPlot", "\345\217\202\350\200\203\350\214\203\345\233\264\357\274\232", 0));
        label_2->setText(QApplication::translate("Pv_AccuracyPlot", "\346\226\271\346\263\225\357\274\232", 0));
        label_8->setText(QApplication::translate("Pv_AccuracyPlot", "\346\243\200\346\265\213\350\214\203\345\233\264\357\274\232", 0));
        label_6->setText(QApplication::translate("Pv_AccuracyPlot", "\346\226\271\346\263\225\357\274\232", 0));
        label->setText(QApplication::translate("Pv_AccuracyPlot", "\344\273\252\345\231\250\357\274\210X\357\274\211\357\274\232", 0));
        groupBox->setTitle(QApplication::translate("Pv_AccuracyPlot", "\345\233\276\350\241\250", 0));
        label_26->setText(QApplication::translate("Pv_AccuracyPlot", "\345\233\276", 0));
        label_27->setText(QApplication::translate("Pv_AccuracyPlot", "\346\226\271\345\267\256\346\257\224\345\267\256\345\200\274\345\233\276", 0));
        label_20->setText(QApplication::translate("Pv_AccuracyPlot", "\345\201\217\345\200\232\345\214\272\351\227\264", 0));
        label_17->setText(QApplication::translate("Pv_AccuracyPlot", "\345\201\217\345\200\232\357\274\232", 0));
        label_18->setText(QApplication::translate("Pv_AccuracyPlot", "\345\201\217\345\200\232\345\214\272\351\227\264\357\274\232", 0));
        label_19->setText(QApplication::translate("Pv_AccuracyPlot", "\350\257\204\345\256\232\346\240\207\345\207\206\357\274\232", 0));
        label_14->setText(QApplication::translate("Pv_AccuracyPlot", "b", 0));
        label_15->setText(QApplication::translate("Pv_AccuracyPlot", "\346\265\213\345\256\232\345\200\274\357\274\232", 0));
        label_9->setText(QApplication::translate("Pv_AccuracyPlot", "\345\233\236\345\275\222\346\226\271\347\250\213\357\274\232", 0));
        label_16->setText(QString());
        pushButton->setText(QApplication::translate("Pv_AccuracyPlot", "\346\237\245\347\234\213\345\256\236\351\252\214\350\246\201\346\261\202", 0));
        pushButton_2->setText(QApplication::translate("Pv_AccuracyPlot", "\346\217\220\344\272\244\346\225\260\346\215\256", 0));
        label_10->setText(QApplication::translate("Pv_AccuracyPlot", "\347\233\270\345\205\263\347\263\273\346\225\260\357\274\232", 0));
        label_11->setText(QApplication::translate("Pv_AccuracyPlot", "\345\214\273\345\255\246\345\206\263\345\256\232\346\260\264\345\271\263\357\274\232", 0));
        label_12->setText(QApplication::translate("Pv_AccuracyPlot", "\351\242\204\346\234\237\345\200\274\357\274\232", 0));
        label_13->setText(QApplication::translate("Pv_AccuracyPlot", "a=", 0));
        label_25->setText(QApplication::translate("Pv_AccuracyPlot", "\346\263\250\351\207\212\357\274\232", 0));
        label_21->setText(QApplication::translate("Pv_AccuracyPlot", "\346\212\200\346\234\257\345\221\230\357\274\232", 0));
        label_22->setText(QApplication::translate("Pv_AccuracyPlot", "\345\256\241\346\240\270\344\272\272\357\274\232", 0));
        label_23->setText(QApplication::translate("Pv_AccuracyPlot", "\346\227\245\346\234\237\357\274\232  ", 0));
        label_24->setText(QApplication::translate("Pv_AccuracyPlot", "\346\227\245\346\234\237\357\274\232 ", 0));
    } // retranslateUi

};

namespace Ui {
    class Pv_AccuracyPlot: public Ui_Pv_AccuracyPlot {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PV_ACCURACYPLOT_H
