/********************************************************************************
** Form generated from reading UI file 'ManageMaterialBatch.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MANAGEMATERIALBATCH_H
#define UI_MANAGEMATERIALBATCH_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ManageMaterialBatch
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout;
    QLineEdit *inputKeyword;
    QTreeWidget *treeWidget;
    QWidget *widget;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_3;
    QTableWidget *table;
    QWidget *widget_3;
    QPushButton *btnAdd;
    QPushButton *btnDelete;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnSave;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QMainWindow *ManageMaterialBatch)
    {
        if (ManageMaterialBatch->objectName().isEmpty())
            ManageMaterialBatch->setObjectName(QStringLiteral("ManageMaterialBatch"));
        ManageMaterialBatch->resize(800, 600);
        centralwidget = new QWidget(ManageMaterialBatch);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(groupBox_3);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        inputKeyword = new QLineEdit(groupBox_3);
        inputKeyword->setObjectName(QStringLiteral("inputKeyword"));

        verticalLayout->addWidget(inputKeyword);

        treeWidget = new QTreeWidget(groupBox_3);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));
        treeWidget->header()->setVisible(false);

        verticalLayout->addWidget(treeWidget);


        horizontalLayout->addWidget(groupBox_3);

        widget = new QWidget(centralwidget);
        widget->setObjectName(QStringLiteral("widget"));
        verticalLayout_3 = new QVBoxLayout(widget);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        groupBox = new QGroupBox(widget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        groupBox_2 = new QGroupBox(groupBox);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        horizontalLayout_3 = new QHBoxLayout(groupBox_2);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        table = new QTableWidget(groupBox_2);
        table->setObjectName(QStringLiteral("table"));

        horizontalLayout_3->addWidget(table);

        widget_3 = new QWidget(groupBox_2);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        widget_3->setMinimumSize(QSize(60, 0));
        btnAdd = new QPushButton(widget_3);
        btnAdd->setObjectName(QStringLiteral("btnAdd"));
        btnAdd->setGeometry(QRect(10, 150, 32, 32));
        btnAdd->setFlat(true);
        btnDelete = new QPushButton(widget_3);
        btnDelete->setObjectName(QStringLiteral("btnDelete"));
        btnDelete->setGeometry(QRect(10, 190, 32, 32));
        btnDelete->setIconSize(QSize(32, 32));
        btnDelete->setFlat(true);

        horizontalLayout_3->addWidget(widget_3);


        verticalLayout_2->addWidget(groupBox_2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        btnSave = new QPushButton(groupBox);
        btnSave->setObjectName(QStringLiteral("btnSave"));

        horizontalLayout_2->addWidget(btnSave);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout_2);


        verticalLayout_3->addWidget(groupBox);


        horizontalLayout->addWidget(widget);

        ManageMaterialBatch->setCentralWidget(centralwidget);

        retranslateUi(ManageMaterialBatch);

        QMetaObject::connectSlotsByName(ManageMaterialBatch);
    } // setupUi

    void retranslateUi(QMainWindow *ManageMaterialBatch)
    {
        ManageMaterialBatch->setWindowTitle(QApplication::translate("ManageMaterialBatch", "MainWindow", 0));
        groupBox_3->setTitle(QString());
        groupBox->setTitle(QString());
        groupBox_2->setTitle(QString());
        btnAdd->setText(QString());
        btnDelete->setText(QString());
        btnSave->setText(QApplication::translate("ManageMaterialBatch", "\344\277\235\345\255\230", 0));
    } // retranslateUi

};

namespace Ui {
    class ManageMaterialBatch: public Ui_ManageMaterialBatch {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MANAGEMATERIALBATCH_H
