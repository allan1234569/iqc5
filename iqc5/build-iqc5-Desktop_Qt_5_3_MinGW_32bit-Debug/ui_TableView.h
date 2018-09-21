/********************************************************************************
** Form generated from reading UI file 'TableView.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TABLEVIEW_H
#define UI_TABLEVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_TableView
{
public:
    QVBoxLayout *verticalLayout;
    QTableWidget *table;

    void setupUi(QDialog *TableView)
    {
        if (TableView->objectName().isEmpty())
            TableView->setObjectName(QStringLiteral("TableView"));
        TableView->resize(710, 476);
        verticalLayout = new QVBoxLayout(TableView);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        table = new QTableWidget(TableView);
        table->setObjectName(QStringLiteral("table"));

        verticalLayout->addWidget(table);


        retranslateUi(TableView);

        QMetaObject::connectSlotsByName(TableView);
    } // setupUi

    void retranslateUi(QDialog *TableView)
    {
        TableView->setWindowTitle(QApplication::translate("TableView", "Dialog", 0));
    } // retranslateUi

};

namespace Ui {
    class TableView: public Ui_TableView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TABLEVIEW_H
