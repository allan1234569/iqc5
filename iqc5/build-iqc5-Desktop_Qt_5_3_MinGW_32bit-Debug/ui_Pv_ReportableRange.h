/********************************************************************************
** Form generated from reading UI file 'Pv_ReportableRange.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PV_REPORTABLERANGE_H
#define UI_PV_REPORTABLERANGE_H

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
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Pv_ReportableRange
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLineEdit *lineEdit_8;
    QLineEdit *RI_XReferenceRange;
    QLineEdit *RI_InstrumentY;
    QLineEdit *RI_XDetectionRange;
    QLineEdit *lineEdit_9;
    QLineEdit *lineEdit_10;
    QLineEdit *RI_InstrumentX;
    QLabel *label_6;
    QSpacerItem *horizontalSpacer_4;
    QLabel *label_13;
    QLabel *label_11;
    QLabel *label_7;
    QLabel *label_12;
    QLineEdit *RI_XScheme;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_8;
    QSpacerItem *horizontalSpacer_5;
    QHBoxLayout *horizontalLayout_4;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_3;
    QTableWidget *RI_Reagen_TableWidget;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_2;
    QTableWidget *RI_Date_TableWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *RI_BtnExperimentalRequirements;
    QSpacerItem *horizontalSpacer;
    QPushButton *RI_BtnCommit;
    QGridLayout *gridLayout_2;
    QLabel *label_4;
    QLineEdit *RI_Technicina;
    QLabel *label_5;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *RI_Auditor;
    QSpacerItem *horizontalSpacer_2;
    QDateEdit *RI_ApprovalDate;
    QDateEdit *RI_CalculateDate;
    QLabel *label;
    QSpacerItem *horizontalSpacer_3;
    QPlainTextEdit *RI_Annotation;

    void setupUi(QDialog *Pv_ReportableRange)
    {
        if (Pv_ReportableRange->objectName().isEmpty())
            Pv_ReportableRange->setObjectName(QStringLiteral("Pv_ReportableRange"));
        Pv_ReportableRange->resize(1047, 678);
        verticalLayout = new QVBoxLayout(Pv_ReportableRange);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        lineEdit_8 = new QLineEdit(Pv_ReportableRange);
        lineEdit_8->setObjectName(QStringLiteral("lineEdit_8"));

        gridLayout->addWidget(lineEdit_8, 1, 4, 1, 1);

        RI_XReferenceRange = new QLineEdit(Pv_ReportableRange);
        RI_XReferenceRange->setObjectName(QStringLiteral("RI_XReferenceRange"));

        gridLayout->addWidget(RI_XReferenceRange, 2, 1, 1, 1);

        RI_InstrumentY = new QLineEdit(Pv_ReportableRange);
        RI_InstrumentY->setObjectName(QStringLiteral("RI_InstrumentY"));

        gridLayout->addWidget(RI_InstrumentY, 0, 4, 1, 1);

        RI_XDetectionRange = new QLineEdit(Pv_ReportableRange);
        RI_XDetectionRange->setObjectName(QStringLiteral("RI_XDetectionRange"));

        gridLayout->addWidget(RI_XDetectionRange, 3, 1, 1, 1);

        lineEdit_9 = new QLineEdit(Pv_ReportableRange);
        lineEdit_9->setObjectName(QStringLiteral("lineEdit_9"));

        gridLayout->addWidget(lineEdit_9, 2, 4, 1, 1);

        lineEdit_10 = new QLineEdit(Pv_ReportableRange);
        lineEdit_10->setObjectName(QStringLiteral("lineEdit_10"));

        gridLayout->addWidget(lineEdit_10, 3, 4, 1, 1);

        RI_InstrumentX = new QLineEdit(Pv_ReportableRange);
        RI_InstrumentX->setObjectName(QStringLiteral("RI_InstrumentX"));

        gridLayout->addWidget(RI_InstrumentX, 0, 1, 1, 1);

        label_6 = new QLabel(Pv_ReportableRange);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout->addWidget(label_6, 0, 0, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 0, 2, 1, 1);

        label_13 = new QLabel(Pv_ReportableRange);
        label_13->setObjectName(QStringLiteral("label_13"));

        gridLayout->addWidget(label_13, 3, 3, 1, 1);

        label_11 = new QLabel(Pv_ReportableRange);
        label_11->setObjectName(QStringLiteral("label_11"));

        gridLayout->addWidget(label_11, 1, 3, 1, 1);

        label_7 = new QLabel(Pv_ReportableRange);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout->addWidget(label_7, 1, 0, 1, 1);

        label_12 = new QLabel(Pv_ReportableRange);
        label_12->setObjectName(QStringLiteral("label_12"));

        gridLayout->addWidget(label_12, 2, 3, 1, 1);

        RI_XScheme = new QLineEdit(Pv_ReportableRange);
        RI_XScheme->setObjectName(QStringLiteral("RI_XScheme"));

        gridLayout->addWidget(RI_XScheme, 1, 1, 1, 1);

        label_9 = new QLabel(Pv_ReportableRange);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout->addWidget(label_9, 3, 0, 1, 1);

        label_10 = new QLabel(Pv_ReportableRange);
        label_10->setObjectName(QStringLiteral("label_10"));

        gridLayout->addWidget(label_10, 0, 3, 1, 1);

        label_8 = new QLabel(Pv_ReportableRange);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout->addWidget(label_8, 2, 0, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_5, 0, 5, 1, 1);

        gridLayout->setColumnStretch(1, 2);
        gridLayout->setColumnStretch(2, 3);
        gridLayout->setColumnStretch(4, 2);
        gridLayout->setColumnStretch(5, 3);

        verticalLayout->addLayout(gridLayout);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        groupBox_2 = new QGroupBox(Pv_ReportableRange);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        horizontalLayout_3 = new QHBoxLayout(groupBox_2);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        RI_Reagen_TableWidget = new QTableWidget(groupBox_2);
        RI_Reagen_TableWidget->setObjectName(QStringLiteral("RI_Reagen_TableWidget"));

        horizontalLayout_3->addWidget(RI_Reagen_TableWidget);

        horizontalLayout_3->setStretch(0, 3);

        horizontalLayout_4->addWidget(groupBox_2);

        groupBox = new QGroupBox(Pv_ReportableRange);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        horizontalLayout_2 = new QHBoxLayout(groupBox);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        RI_Date_TableWidget = new QTableWidget(groupBox);
        RI_Date_TableWidget->setObjectName(QStringLiteral("RI_Date_TableWidget"));

        horizontalLayout_2->addWidget(RI_Date_TableWidget);


        horizontalLayout_4->addWidget(groupBox);

        horizontalLayout_4->setStretch(0, 3);
        horizontalLayout_4->setStretch(1, 3);

        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        RI_BtnExperimentalRequirements = new QPushButton(Pv_ReportableRange);
        RI_BtnExperimentalRequirements->setObjectName(QStringLiteral("RI_BtnExperimentalRequirements"));

        horizontalLayout->addWidget(RI_BtnExperimentalRequirements);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        RI_BtnCommit = new QPushButton(Pv_ReportableRange);
        RI_BtnCommit->setObjectName(QStringLiteral("RI_BtnCommit"));

        horizontalLayout->addWidget(RI_BtnCommit);


        verticalLayout->addLayout(horizontalLayout);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label_4 = new QLabel(Pv_ReportableRange);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout_2->addWidget(label_4, 0, 3, 1, 1);

        RI_Technicina = new QLineEdit(Pv_ReportableRange);
        RI_Technicina->setObjectName(QStringLiteral("RI_Technicina"));

        gridLayout_2->addWidget(RI_Technicina, 0, 1, 1, 1);

        label_5 = new QLabel(Pv_ReportableRange);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout_2->addWidget(label_5, 1, 3, 1, 1);

        label_2 = new QLabel(Pv_ReportableRange);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_2->addWidget(label_2, 1, 0, 1, 1);

        label_3 = new QLabel(Pv_ReportableRange);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout_2->addWidget(label_3, 2, 0, 1, 1);

        RI_Auditor = new QLineEdit(Pv_ReportableRange);
        RI_Auditor->setObjectName(QStringLiteral("RI_Auditor"));

        gridLayout_2->addWidget(RI_Auditor, 1, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 0, 2, 1, 1);

        RI_ApprovalDate = new QDateEdit(Pv_ReportableRange);
        RI_ApprovalDate->setObjectName(QStringLiteral("RI_ApprovalDate"));
        RI_ApprovalDate->setCalendarPopup(true);

        gridLayout_2->addWidget(RI_ApprovalDate, 1, 4, 1, 1);

        RI_CalculateDate = new QDateEdit(Pv_ReportableRange);
        RI_CalculateDate->setObjectName(QStringLiteral("RI_CalculateDate"));
        RI_CalculateDate->setCalendarPopup(true);

        gridLayout_2->addWidget(RI_CalculateDate, 0, 4, 1, 1);

        label = new QLabel(Pv_ReportableRange);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_3, 0, 5, 1, 1);

        RI_Annotation = new QPlainTextEdit(Pv_ReportableRange);
        RI_Annotation->setObjectName(QStringLiteral("RI_Annotation"));
        RI_Annotation->setMaximumSize(QSize(16777215, 40));

        gridLayout_2->addWidget(RI_Annotation, 2, 1, 1, 4);

        gridLayout_2->setColumnStretch(1, 2);
        gridLayout_2->setColumnStretch(2, 4);
        gridLayout_2->setColumnStretch(4, 2);
        gridLayout_2->setColumnStretch(5, 4);

        verticalLayout->addLayout(gridLayout_2);

        verticalLayout->setStretch(1, 5);

        retranslateUi(Pv_ReportableRange);

        QMetaObject::connectSlotsByName(Pv_ReportableRange);
    } // setupUi

    void retranslateUi(QDialog *Pv_ReportableRange)
    {
        Pv_ReportableRange->setWindowTitle(QApplication::translate("Pv_ReportableRange", "Dialog", 0));
        label_6->setText(QApplication::translate("Pv_ReportableRange", "\344\273\252\345\231\250\357\274\210X\357\274\211\357\274\232", 0));
        label_13->setText(QApplication::translate("Pv_ReportableRange", "\346\243\200\351\252\214\350\214\203\345\233\264\357\274\232", 0));
        label_11->setText(QApplication::translate("Pv_ReportableRange", "\346\226\271\346\263\225\357\274\232", 0));
        label_7->setText(QApplication::translate("Pv_ReportableRange", "\346\226\271\346\263\225\357\274\232", 0));
        label_12->setText(QApplication::translate("Pv_ReportableRange", "\345\217\202\350\200\203\350\214\203\345\233\264\357\274\232", 0));
        label_9->setText(QApplication::translate("Pv_ReportableRange", "\346\243\200\351\252\214\350\214\203\345\233\264\357\274\232", 0));
        label_10->setText(QApplication::translate("Pv_ReportableRange", "\344\273\252\345\231\250\357\274\210Y\357\274\211\357\274\232", 0));
        label_8->setText(QApplication::translate("Pv_ReportableRange", "\345\217\202\350\200\203\350\214\203\345\233\264\357\274\232", 0));
        groupBox_2->setTitle(QApplication::translate("Pv_ReportableRange", "\350\257\225\345\211\202", 0));
        groupBox->setTitle(QApplication::translate("Pv_ReportableRange", "\346\225\260\346\215\256\346\200\273\347\273\223", 0));
        RI_BtnExperimentalRequirements->setText(QApplication::translate("Pv_ReportableRange", "\346\237\245\347\234\213\345\256\236\351\252\214\350\246\201\346\261\202", 0));
        RI_BtnCommit->setText(QApplication::translate("Pv_ReportableRange", "\346\217\220\344\272\244\346\225\260\346\215\256", 0));
        label_4->setText(QApplication::translate("Pv_ReportableRange", "\346\227\245\346\234\237\357\274\232", 0));
        label_5->setText(QApplication::translate("Pv_ReportableRange", "\346\227\245\346\234\237\357\274\232", 0));
        label_2->setText(QApplication::translate("Pv_ReportableRange", "\345\256\241\346\240\270\344\272\272\357\274\232", 0));
        label_3->setText(QApplication::translate("Pv_ReportableRange", "\346\263\250\351\207\212\357\274\232", 0));
        label->setText(QApplication::translate("Pv_ReportableRange", "\346\212\200\346\234\257\345\221\230\357\274\232", 0));
    } // retranslateUi

};

namespace Ui {
    class Pv_ReportableRange: public Ui_Pv_ReportableRange {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PV_REPORTABLERANGE_H
