/********************************************************************************
** Form generated from reading UI file 'ManageDevice.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MANAGEDEVICE_H
#define UI_MANAGEDEVICE_H

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

class Ui_ManageDevice
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *inputKeyword;
    QTreeWidget *treeWidget;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QTableWidget *table;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnAdd;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QMainWindow *ManageDevice)
    {
        if (ManageDevice->objectName().isEmpty())
            ManageDevice->setObjectName(QStringLiteral("ManageDevice"));
        ManageDevice->resize(800, 600);
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/clipboard.png"), QSize(), QIcon::Normal, QIcon::Off);
        ManageDevice->setWindowIcon(icon);
        centralwidget = new QWidget(ManageDevice);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setMaximumSize(QSize(200, 16777215));
        verticalLayout_2 = new QVBoxLayout(groupBox_3);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        inputKeyword = new QLineEdit(groupBox_3);
        inputKeyword->setObjectName(QStringLiteral("inputKeyword"));

        verticalLayout_2->addWidget(inputKeyword);

        treeWidget = new QTreeWidget(groupBox_3);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));
        treeWidget->setMaximumSize(QSize(16777215, 16777215));
        treeWidget->header()->setVisible(false);

        verticalLayout_2->addWidget(treeWidget);


        horizontalLayout->addWidget(groupBox_3);

        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        table = new QTableWidget(groupBox);
        table->setObjectName(QStringLiteral("table"));

        verticalLayout->addWidget(table);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        btnAdd = new QPushButton(groupBox);
        btnAdd->setObjectName(QStringLiteral("btnAdd"));

        horizontalLayout_2->addWidget(btnAdd);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_2);


        horizontalLayout->addWidget(groupBox);

        ManageDevice->setCentralWidget(centralwidget);

        retranslateUi(ManageDevice);

        QMetaObject::connectSlotsByName(ManageDevice);
    } // setupUi

    void retranslateUi(QMainWindow *ManageDevice)
    {
        ManageDevice->setWindowTitle(QApplication::translate("ManageDevice", "\344\273\252\345\231\250\347\273\264\346\212\244", 0));
        groupBox_3->setTitle(QString());
        groupBox->setTitle(QString());
        btnAdd->setText(QApplication::translate("ManageDevice", "\346\267\273\345\212\240", 0));
    } // retranslateUi

};

namespace Ui {
    class ManageDevice: public Ui_ManageDevice {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MANAGEDEVICE_H
