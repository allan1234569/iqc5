/********************************************************************************
** Form generated from reading UI file 'ManageDataImport.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MANAGEDATAIMPORT_H
#define UI_MANAGEDATAIMPORT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>

QT_BEGIN_NAMESPACE

class Ui_ManageDataImport
{
public:
    QPushButton *Ensure_PushButton;
    QTableWidget *tableWidget;
    QPushButton *Cancel_PushButton;
    QPushButton *Save_PushButton;
    QToolButton *Delete_ToolButton;
    QToolButton *Add_ToolButton;
    QLabel *label;
    QLineEdit *filepath_LineEdit;
    QPushButton *BtnSelectPath;

    void setupUi(QDialog *ManageDataImport)
    {
        if (ManageDataImport->objectName().isEmpty())
            ManageDataImport->setObjectName(QStringLiteral("ManageDataImport"));
        ManageDataImport->resize(469, 382);
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/clipboard.png"), QSize(), QIcon::Normal, QIcon::Off);
        ManageDataImport->setWindowIcon(icon);
        Ensure_PushButton = new QPushButton(ManageDataImport);
        Ensure_PushButton->setObjectName(QStringLiteral("Ensure_PushButton"));
        Ensure_PushButton->setGeometry(QRect(40, 350, 70, 23));
        tableWidget = new QTableWidget(ManageDataImport);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(10, 40, 410, 300));
        tableWidget->setGridStyle(Qt::SolidLine);
        tableWidget->setColumnCount(3);
        tableWidget->verticalHeader()->setVisible(false);
        Cancel_PushButton = new QPushButton(ManageDataImport);
        Cancel_PushButton->setObjectName(QStringLiteral("Cancel_PushButton"));
        Cancel_PushButton->setGeometry(QRect(310, 350, 60, 23));
        Save_PushButton = new QPushButton(ManageDataImport);
        Save_PushButton->setObjectName(QStringLiteral("Save_PushButton"));
        Save_PushButton->setGeometry(QRect(170, 350, 60, 23));
        Delete_ToolButton = new QToolButton(ManageDataImport);
        Delete_ToolButton->setObjectName(QStringLiteral("Delete_ToolButton"));
        Delete_ToolButton->setGeometry(QRect(430, 100, 30, 30));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/images/Remove_213px.png"), QSize(), QIcon::Normal, QIcon::Off);
        Delete_ToolButton->setIcon(icon1);
        Delete_ToolButton->setIconSize(QSize(20, 20));
        Add_ToolButton = new QToolButton(ManageDataImport);
        Add_ToolButton->setObjectName(QStringLiteral("Add_ToolButton"));
        Add_ToolButton->setGeometry(QRect(430, 60, 30, 30));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/images/Add_213px.png"), QSize(), QIcon::Normal, QIcon::Off);
        Add_ToolButton->setIcon(icon2);
        Add_ToolButton->setIconSize(QSize(20, 20));
        label = new QLabel(ManageDataImport);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 10, 60, 20));
        filepath_LineEdit = new QLineEdit(ManageDataImport);
        filepath_LineEdit->setObjectName(QStringLiteral("filepath_LineEdit"));
        filepath_LineEdit->setGeometry(QRect(90, 10, 330, 20));
        filepath_LineEdit->setReadOnly(true);
        BtnSelectPath = new QPushButton(ManageDataImport);
        BtnSelectPath->setObjectName(QStringLiteral("BtnSelectPath"));
        BtnSelectPath->setGeometry(QRect(430, 10, 30, 23));

        retranslateUi(ManageDataImport);

        QMetaObject::connectSlotsByName(ManageDataImport);
    } // setupUi

    void retranslateUi(QDialog *ManageDataImport)
    {
        ManageDataImport->setWindowTitle(QApplication::translate("ManageDataImport", "\346\225\260\346\215\256\345\257\274\345\205\245\350\256\276\347\275\256", 0));
        Ensure_PushButton->setText(QApplication::translate("ManageDataImport", "\344\277\235\345\255\230\345\271\266\351\200\200\345\207\272", 0));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("ManageDataImport", "\346\240\267\346\234\254\345\217\267", 0));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("ManageDataImport", "\351\241\271\347\233\256\345\220\215\347\247\260", 0));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("ManageDataImport", "\346\265\223\345\272\246\346\260\264\345\271\263", 0));
        Cancel_PushButton->setText(QApplication::translate("ManageDataImport", "\345\217\226 \346\266\210", 0));
        Save_PushButton->setText(QApplication::translate("ManageDataImport", "\344\277\235 \345\255\230", 0));
        Delete_ToolButton->setText(QString());
        Add_ToolButton->setText(QString());
        label->setText(QApplication::translate("ManageDataImport", " \346\226\207\344\273\266\350\267\257\345\276\204\357\274\232", 0));
        BtnSelectPath->setText(QApplication::translate("ManageDataImport", "...", 0));
    } // retranslateUi

};

namespace Ui {
    class ManageDataImport: public Ui_ManageDataImport {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MANAGEDATAIMPORT_H
