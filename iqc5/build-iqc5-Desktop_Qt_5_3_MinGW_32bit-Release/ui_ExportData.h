/********************************************************************************
** Form generated from reading UI file 'ExportData.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXPORTDATA_H
#define UI_EXPORTDATA_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ExportData
{
public:
    QPushButton *export_Btn;
    QPushButton *cancel_Btn;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QTreeWidget *treeWidget;
    QGroupBox *groupBox_2;
    QDateEdit *startDate;
    QDateEdit *endDate;
    QLabel *label_3;
    QLabel *label;
    QCheckBox *checkBox;

    void setupUi(QWidget *ExportData)
    {
        if (ExportData->objectName().isEmpty())
            ExportData->setObjectName(QStringLiteral("ExportData"));
        ExportData->resize(560, 430);
        ExportData->setMinimumSize(QSize(560, 430));
        ExportData->setMaximumSize(QSize(560, 430));
        export_Btn = new QPushButton(ExportData);
        export_Btn->setObjectName(QStringLiteral("export_Btn"));
        export_Btn->setGeometry(QRect(120, 390, 60, 30));
        cancel_Btn = new QPushButton(ExportData);
        cancel_Btn->setObjectName(QStringLiteral("cancel_Btn"));
        cancel_Btn->setGeometry(QRect(320, 390, 60, 30));
        groupBox = new QGroupBox(ExportData);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 211, 370));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(6, 6, 6, 6);
        treeWidget = new QTreeWidget(groupBox);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("\351\241\271\347\233\256"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));
        treeWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        treeWidget->header()->setVisible(true);

        verticalLayout->addWidget(treeWidget);

        groupBox_2 = new QGroupBox(ExportData);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(230, 10, 320, 370));
        startDate = new QDateEdit(groupBox_2);
        startDate->setObjectName(QStringLiteral("startDate"));
        startDate->setGeometry(QRect(100, 60, 110, 22));
        startDate->setCalendarPopup(true);
        endDate = new QDateEdit(groupBox_2);
        endDate->setObjectName(QStringLiteral("endDate"));
        endDate->setGeometry(QRect(100, 100, 110, 22));
        endDate->setCalendarPopup(true);
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(30, 60, 60, 20));
        label = new QLabel(groupBox_2);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 100, 60, 20));
        checkBox = new QCheckBox(groupBox_2);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setGeometry(QRect(30, 30, 71, 16));

        retranslateUi(ExportData);

        QMetaObject::connectSlotsByName(ExportData);
    } // setupUi

    void retranslateUi(QWidget *ExportData)
    {
        ExportData->setWindowTitle(QApplication::translate("ExportData", "\346\225\260\346\215\256\345\257\274\345\207\272", 0));
        export_Btn->setText(QApplication::translate("ExportData", "\345\257\274 \345\207\272", 0));
        cancel_Btn->setText(QApplication::translate("ExportData", "\345\217\226 \346\266\210", 0));
        groupBox->setTitle(QApplication::translate("ExportData", "\351\241\271\347\233\256\351\200\211\346\213\251", 0));
        groupBox_2->setTitle(QApplication::translate("ExportData", "\347\255\233\351\200\211", 0));
        startDate->setDisplayFormat(QApplication::translate("ExportData", "yyyy-MM-dd", 0));
        endDate->setDisplayFormat(QApplication::translate("ExportData", "yyyy-MM-dd", 0));
        label_3->setText(QApplication::translate("ExportData", "\350\265\267\345\247\213\346\227\245\346\234\237\357\274\232", 0));
        label->setText(QApplication::translate("ExportData", "\347\273\210\346\255\242\346\227\245\346\234\237\357\274\232", 0));
        checkBox->setText(QApplication::translate("ExportData", "\345\220\257\347\224\250\347\255\233\351\200\211", 0));
    } // retranslateUi

};

namespace Ui {
    class ExportData: public Ui_ExportData {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXPORTDATA_H
