/********************************************************************************
** Form generated from reading UI file 'ManageType.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MANAGETYPE_H
#define UI_MANAGETYPE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ManageType
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_2;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_3;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *inputKeyword;
    QTreeWidget *treeWidget;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QLineEdit *txtName;
    QPushButton *btnSearch;
    QLabel *label_2;
    QComboBox *inputSubject;
    QComboBox *inputCategory;
    QLabel *label;
    QLabel *label_4;
    QTableWidget *table;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnAdd;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QMainWindow *ManageType)
    {
        if (ManageType->objectName().isEmpty())
            ManageType->setObjectName(QStringLiteral("ManageType"));
        ManageType->resize(800, 600);
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/clipboard.png"), QSize(), QIcon::Normal, QIcon::Off);
        ManageType->setWindowIcon(icon);
        centralwidget = new QWidget(ManageType);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        horizontalLayout_2 = new QHBoxLayout(centralwidget);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setMinimumSize(QSize(0, 0));
        widget->setMaximumSize(QSize(200, 16777215));
        horizontalLayout_3 = new QHBoxLayout(widget);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        groupBox_3 = new QGroupBox(widget);
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


        horizontalLayout_3->addWidget(groupBox_3);


        horizontalLayout_2->addWidget(widget);

        widget_2 = new QWidget(centralwidget);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        verticalLayout = new QVBoxLayout(widget_2);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        groupBox = new QGroupBox(widget_2);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setMinimumSize(QSize(0, 50));
        txtName = new QLineEdit(groupBox);
        txtName->setObjectName(QStringLiteral("txtName"));
        txtName->setGeometry(QRect(370, 18, 113, 20));
        btnSearch = new QPushButton(groupBox);
        btnSearch->setObjectName(QStringLiteral("btnSearch"));
        btnSearch->setGeometry(QRect(504, 18, 75, 21));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(340, 20, 31, 16));
        inputSubject = new QComboBox(groupBox);
        inputSubject->setObjectName(QStringLiteral("inputSubject"));
        inputSubject->setGeometry(QRect(40, 18, 141, 22));
        inputCategory = new QComboBox(groupBox);
        inputCategory->setObjectName(QStringLiteral("inputCategory"));
        inputCategory->setGeometry(QRect(230, 18, 101, 22));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 20, 31, 16));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(190, 20, 41, 16));

        verticalLayout->addWidget(groupBox);

        table = new QTableWidget(widget_2);
        table->setObjectName(QStringLiteral("table"));

        verticalLayout->addWidget(table);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnAdd = new QPushButton(widget_2);
        btnAdd->setObjectName(QStringLiteral("btnAdd"));

        horizontalLayout->addWidget(btnAdd);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);


        horizontalLayout_2->addWidget(widget_2);

        ManageType->setCentralWidget(centralwidget);

        retranslateUi(ManageType);

        QMetaObject::connectSlotsByName(ManageType);
    } // setupUi

    void retranslateUi(QMainWindow *ManageType)
    {
        ManageType->setWindowTitle(QApplication::translate("ManageType", "\351\241\271\347\233\256\347\256\241\347\220\206", 0));
        groupBox_3->setTitle(QString());
        groupBox->setTitle(QApplication::translate("ManageType", "\346\237\245\350\257\242", 0));
        btnSearch->setText(QApplication::translate("ManageType", "\346\237\245\350\257\242", 0));
        label_2->setText(QApplication::translate("ManageType", "\351\241\271\347\233\256", 0));
        label->setText(QApplication::translate("ManageType", "\344\270\223\344\270\232", 0));
        label_4->setText(QApplication::translate("ManageType", "\344\272\232\344\270\223\344\270\232", 0));
        btnAdd->setText(QApplication::translate("ManageType", "\346\267\273\345\212\240", 0));
    } // retranslateUi

};

namespace Ui {
    class ManageType: public Ui_ManageType {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MANAGETYPE_H
